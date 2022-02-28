#include "libft.h"

char *ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	int		i;

	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while(*s1)
		join[i++] = *s1++;
	while(*s2)
		join[i++] = *s2++;
	join[i] = 0;
	return (join);
}