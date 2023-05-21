#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

/* NO SE PERMITEN ELEMENTOS IGUALES EN EL ARBOL */

struct _s_abb
{
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b)
{
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b)
{
    return a < b;
}

static bool invrep(abb tree)
{
    bool valanciado = true;

    if (tree == NULL) // Nodo vacio
    {
        valanciado = true;
    }
    else if (tree->left != NULL && tree->right != NULL) // Nodo con las dos ramas.
    {
        valanciado = elem_less(tree->left->elem, tree->elem) && invrep(tree->left) && !elem_eq(tree->left->elem, tree->elem);
        valanciado = elem_less(tree->elem, tree->right->elem) && !elem_eq(tree->elem, tree->right->elem) && invrep(tree->right) && valanciado;
    }
    else if (tree->left != NULL && tree->right == NULL) // Nodo con la rama izq.
    {
        valanciado = elem_less(tree->left->elem, tree->elem) && !elem_eq(tree->left->elem, tree->elem) && invrep(tree->left) && valanciado;
    }
    else if (tree->left == NULL && tree->right != NULL) // Nodo con la rama der.
    {
        valanciado = elem_less(tree->elem, tree->right->elem) && !elem_eq(tree->elem, tree->right->elem) && invrep(tree->right) && valanciado;
    }
    return valanciado;
}

static abb create_node(abb_elem e)
{
    struct _s_abb *new_node = malloc(sizeof(struct _s_abb));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->left = NULL;
    new_node->right = NULL;
    assert(invrep(new_node));
    return new_node;
}

static abb delete_root(abb tree)
{
    assert(invrep(tree) && !abb_is_empty(tree));
    struct _s_abb *killme = NULL, *tree_aux = tree;
    if (abb_is_empty(tree->left) && !abb_is_empty(tree->right)) // Si la rama izquierda es vacia entoces eliminamos y remplazamos por la rama derecha.
    {
        killme = tree;
        tree = tree->right;
        free(killme);
        killme = NULL;
    }
    else if (!abb_is_empty(tree->left) && abb_is_empty(tree->right)) // Si la rama derecha es vacia entoces eliminamos y remplazamos por la rama izquierda.
    {
        killme = tree;
        tree = tree->left;
        free(killme);
        killme = NULL;
    }
    else if (abb_is_empty(tree->left) && abb_is_empty(tree->right)) // Si la ambas ramas son vacias, eliminamos el elemento.
    {
        free(tree);
        tree = NULL;
    }
    else if (abb_is_empty(tree->right->left))
    {
        tree->elem = tree->right->elem; // Remplazamos el elemento que queremos borrar (la raiz) por el minimo, de esta forma mantenemos las condiciones de abb.
        killme = tree->right;
        tree->right = tree->right->right;

        free(killme);  // Solo elminamos la tupla porque, la key y el value se siguen usando
        killme = NULL; // Eliminamos el minimo, que ya lo pusimos en la raiz.
    }
    else // En este punto tenemos que el nodo tiene ambas ramas.
    {
        tree_aux = tree->right; // Avanzamos a la rama derecha.
        /*  Iteramos hasta llegar al anterior del minimo de la rama derecha,
            esto se hace llendo todo lo posible hasta la izquierda*/
        while (!abb_is_empty(tree_aux->left) && !abb_is_empty(tree_aux->left->left))
        {
            tree_aux = tree_aux->left;
        }
        // En este punto tenemos en tree_aux elemento anterior al minimo => (tree_aux->left es el minimo)
        tree->elem = tree_aux->left->elem; // Remplazamos el elemento que queremos borrar (la raiz) por el minimo, de esta forma mantenemos las condiciones de abb.
        killme = tree_aux->left;
        tree_aux->left = tree_aux->left->right; // Apuntamos el anterior al minimo a la rama izquierda del minimo.
        free(killme);                           // Eliminamos el minimo, que ya lo pusimos en la raiz.
        killme = NULL;
    }
    return tree;
}

static abb abb_node_before(abb tree, abb_elem elem)
{
    struct _s_abb *tree_aux = tree;
    if (abb_is_empty(tree_aux->left) && !abb_is_empty(tree_aux->right))
    {
        if (!elem_eq(tree_aux->right->elem, elem))
        {
            tree_aux = abb_node_before(tree_aux->right, elem);
        }
    }
    else if (!abb_is_empty(tree_aux->left) && abb_is_empty(tree_aux->right))
    {
        if (!elem_eq(tree_aux->left->elem, elem))
        {
            tree_aux = abb_node_before(tree_aux->left, elem);
        }
    }
    else if (!abb_is_empty(tree_aux->left) && !abb_is_empty(tree_aux->right))
    {
        if (!elem_eq(tree_aux->left->elem, elem) && !elem_eq(tree_aux->right->elem, elem))
        {
            if (elem_less(elem, tree_aux->elem))
            {
                tree_aux = abb_node_before(tree_aux->left, elem);
            }
            else
            {
                tree_aux = abb_node_before(tree_aux->right, elem);
            }
        }
    }
    else
    {
        tree_aux = NULL;
    }

    return tree_aux;
}

abb abb_empty(void)
{
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e)
{
    assert(invrep(tree));
    if (abb_is_empty(tree))
    {
        tree = create_node(e);
    }
    else if (elem_less(e, tree->elem))
    {
        tree->left = abb_add(tree->left, e);
    }
    else if (elem_less(tree->elem, e))
    {
        tree->right = abb_add(tree->right, e);
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree)
{
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e)
{
    bool exists = false;
    assert(invrep(tree));
    if (abb_is_empty(tree))
    {
        exists = false;
    }
    else if (elem_less(e, tree->elem))
    {
        exists = abb_exists(tree->left, e);
    }
    else if (elem_eq(e, tree->elem))
    {
        exists = true;
    }
    else
    {
        exists = abb_exists(tree->right, e);
    }
    return exists;
}

unsigned int abb_length(abb tree)
{
    unsigned int length = 0u;
    assert(invrep(tree));
    if (!abb_is_empty(tree))
    {
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e)
{
    assert(invrep(tree));
    struct _s_abb *tree_aux = NULL;

    if (elem_eq(tree->elem, e)) // Si queremos borrar la raiz.
    {
        tree = delete_root(tree);
    }
    else
    {
        tree_aux = abb_node_before(tree, e);
        // En este punto tenemos que en el nodo tree_aux esta elemento anterior al que queremos borrar. (e esta a la izquierda o a la derecha)
        if (!abb_is_empty(tree_aux))
        {
            if (elem_eq(e, tree_aux->left->elem))
            {
                tree_aux->left = delete_root(tree_aux->left);
            }
            else
            {
                tree_aux->right = delete_root(tree_aux->right);
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree)
{
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree)
{
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (!abb_is_empty(tree->right))
    {
        max_e = abb_max(tree->right);
    }
    else
    {
        max_e = tree->elem;
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree)
{
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (!abb_is_empty(tree->left))
    {
        min_e = abb_min(tree->left);
    }
    else
    {
        min_e = tree->elem;
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree)
{
    assert(invrep(tree));
    if (tree != NULL)
    {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree)
{
    assert(invrep(tree));
    struct _s_abb *killme = NULL;
    if (!abb_is_empty(tree))
    {
        killme = tree;
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(killme);
        tree = NULL;
    }

    assert(tree == NULL);
    return tree;
}

/*
    c)
    void abb_dump(abb tree)
    {
        assert(invrep(tree));
        if (tree != NULL)
        {
            abb_dump(tree->left);
            printf("%d ", tree->elem);
            abb_dump(tree->right);
        }
    }
*/