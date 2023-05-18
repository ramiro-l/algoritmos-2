#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

size_t string_length(const char *str)
{
    assert(str != NULL);
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

char *string_filter(const char *str, char c)
{
    size_t length = string_length(str);
    char *new_str = NULL;
    unsigned int j = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] != c)
        {
            new_str = realloc(new_str, sizeof(char) * (j + 1));
            new_str[j] = str[i];
            j++;
        }
    }

    new_str = realloc(new_str, sizeof(char) * (j + 1));
    new_str[j + 1] = '\0';

    return new_str;
}
