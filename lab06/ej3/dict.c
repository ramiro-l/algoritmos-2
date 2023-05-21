#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"
#include "string.h"

struct _node_t
{
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d)
{
    bool valanciado = true;

    if (d == NULL) // Nodo vacio
    {
        valanciado = true;
    }
    else if (d->left != NULL && d->right != NULL) // Nodo con las dos ramas.
    {
        valanciado = key_less(d->left->key, d->key) && !key_eq(d->left->key, d->key) && invrep(d->left);
        valanciado = key_less(d->key, d->right->key) && !key_eq(d->key, d->right->key) && invrep(d->right) && valanciado;
    }
    else if (d->left != NULL && d->right == NULL) // Nodo con la rama izq.
    {
        valanciado = key_less(d->left->key, d->key) && !key_eq(d->left->key, d->key) && invrep(d->left) && valanciado;
    }
    else if (d->left == NULL && d->right != NULL) // Nodo con la rama der.
    {
        valanciado = key_less(d->key, d->right->key) && !key_eq(d->key, d->right->key) && invrep(d->right) && valanciado;
    }
    return valanciado;
}

static bool dict_is_empty(dict_t d)
{
    return d == NULL;
}

static dict_t create_node(key_t k, value_t v)
{
    struct _node_t *new_node = malloc(sizeof(struct _node_t));
    assert(new_node != NULL);
    new_node->key = k;
    new_node->value = v;
    new_node->left = NULL;
    new_node->right = NULL;
    assert(invrep(new_node));
    return new_node;
}

static struct _node_t *destroy_node(struct _node_t *kill)
{
    kill->key = key_destroy(kill->key);
    kill->value = value_destroy(kill->value);
    free(kill);
    kill = NULL;
    return kill;
}

static dict_t delete_root(dict_t d)
{
    assert(invrep(d) && !dict_is_empty(d));
    struct _node_t *killme = NULL, *d_aux = NULL;
    if (dict_is_empty(d->left) && !dict_is_empty(d->right)) // Si la rama izquierda es vacia entoces eliminamos y remplazamos por la rama derecha.
    {
        killme = d;
        d = d->right;
        killme = destroy_node(killme);
    }
    else if (!dict_is_empty(d->left) && dict_is_empty(d->right)) // Si la rama derecha es vacia entoces eliminamos y remplazamos por la rama izquierda.
    {
        killme = d;
        d = d->left;
        killme = destroy_node(killme);
    }
    else if (dict_is_empty(d->left) && dict_is_empty(d->right)) // Si la ambas ramas son vacias, eliminamos el elemento.
    {
        d = destroy_node(d);
    }
    else if (dict_is_empty(d->right->left))
    {

        // Remplazamos el elemento que queremos borrar (la raiz) por el de la derecha, de esta forma mantenemos las condiciones de abb.
        d->key = key_destroy(d->key);
        d->value = value_destroy(d->value);
        d->key = string_clone(d->right->key);
        d->value = string_clone(d->right->value);

        killme = d->right;

        d->right = d->right->right;

        killme = destroy_node(killme); // Eliminamos el minimo, que ya lo pusimos en la raiz.
    }
    else
    {
        d_aux = d->right;
        while (!dict_is_empty(d_aux->left->left))
        {
            d_aux = d_aux->left;
        }
        // En este punto tenemos en d_aux elemento anterior al minimo => (d_aux->left es el minimo)
        d->key = key_destroy(d->key);
        d->value = value_destroy(d->value);
        d->key = string_clone(d_aux->left->key);
        d->value = string_clone(d_aux->left->value); // Remplazamos el elemento que queremos borrar (la raiz) por el minimo, de esta forma mantenemos las condiciones de abb.

        killme = d_aux->left;

        d_aux->left = d_aux->left->right; // Apuntamos el anterior al minimo a la rama izquierda del minimo.

        killme = destroy_node(killme); // Eliminamos el minimo, que ya lo pusimos en la raiz.
    }

    return d;
}

static dict_t dict_node_before(dict_t dict, key_t word)
{
    struct _node_t *dict_aux = dict;
    if (dict_is_empty(dict_aux->left) && !dict_is_empty(dict_aux->right))
    {
        if (!key_eq(dict_aux->right->key, word))
        {
            dict_aux = dict_node_before(dict_aux->right, word);
        }
    }
    else if (!dict_is_empty(dict_aux->left) && dict_is_empty(dict_aux->right))
    {
        if (!key_eq(dict_aux->left->key, word))
        {
            dict_aux = dict_node_before(dict_aux->left, word);
        }
    }
    else if (!dict_is_empty(dict_aux->left) && !dict_is_empty(dict_aux->right))
    {
        if (!key_eq(dict_aux->left->key, word) && !key_eq(dict_aux->right->key, word))
        {
            if (key_less(word, dict_aux->key))
            {
                dict_aux = dict_node_before(dict_aux->left, word);
            }
            else
            {
                dict_aux = dict_node_before(dict_aux->right, word);
            }
        }
    }
    else
    {
        dict_aux = NULL;
    }

    return dict_aux;
}

dict_t dict_empty(void)
{
    dict_t dict = NULL;
    assert(invrep(dict) && dict_is_empty(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def)
{
    assert(invrep(dict));
    if (dict_is_empty(dict))
    {
        dict = create_node(word, def);
    }
    else if (key_less(word, dict->key))
    {
        dict->left = dict_add(dict->left, word, def);
    }
    else if (key_less(dict->key, word))
    {
        dict->right = dict_add(dict->right, word, def);
    }
    else if (key_eq(dict->key, word))
    {
        dict = destroy_node(dict);
        dict = create_node(word, def);
    }
    assert(invrep(dict) && dict_exists(dict, word) && key_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word)
{
    key_t def = NULL;
    assert(invrep(dict));
    if (dict_is_empty(dict))
    {
        def = NULL;
    }
    else if (key_less(word, dict->key))
    {
        def = dict_search(dict->left, word);
    }
    else if (key_eq(word, dict->key))
    {
        def = dict->value;
    }
    else
    {
        def = dict_search(dict->right, word);
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word)
{
    bool exists = false;
    assert(invrep(dict));
    if (dict_is_empty(dict))
    {
        exists = false;
    }
    else if (key_less(word, dict->key))
    {
        exists = dict_exists(dict->left, word);
    }
    else if (key_eq(word, dict->key))
    {
        exists = true;
    }
    else
    {
        exists = dict_exists(dict->right, word);
    }
    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict)
{
    unsigned int length = 0u;
    assert(invrep(dict));
    if (!dict_is_empty(dict))
    {
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    assert(invrep(dict) && (dict_is_empty(dict) || length > 0));
    return length;
}

dict_t dict_remove(dict_t dict, key_t word)
{
    assert(invrep(dict));
    struct _node_t *dict_aux = NULL;

    if (key_eq(dict->key, word)) // Si queremos borrar la raiz.
    {
        dict = delete_root(dict);
    }
    else
    {
        dict_aux = dict_node_before(dict, word);
        // En este punto tenemos que en el nodo dict_aux esta elemento anterior al que queremos borrar. (e esta a la izquierda o a la derecha)
        if (!dict_is_empty(dict_aux))
        {
            if (!dict_is_empty(dict_aux->left) && key_eq(word, dict_aux->left->key))
            {
                dict_aux->left = delete_root(dict_aux->left);
            }
            else
            {
                dict_aux->right = delete_root(dict_aux->right);
            }
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict)
{
    assert(invrep(dict));
    dict = dict_destroy(dict);
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file)
{
    assert(invrep(dict) && file != NULL);
    if (dict != NULL)
    {
        dict_dump(dict->left, file);
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict)
{
    assert(invrep(dict));
    struct _node_t *killme = NULL;
    if (!dict_is_empty(dict))
    {
        killme = dict;
        dict_destroy(dict->left);
        dict_destroy(dict->right);
        killme = destroy_node(killme);
        dict = NULL;
    }

    assert(dict == NULL);
    return dict;
}
