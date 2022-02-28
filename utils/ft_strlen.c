#include "libc.h"

size_t ft_strlen(const char *str)
{
    size_t cont;

    cont = 0;
    while(str[cont])
        cont++;
    return (cont);
}