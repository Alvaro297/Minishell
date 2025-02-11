# include "libft.h"

char *ft_strndup(const char *s, size_t len)
{
	char *dup = malloc(len + 1);
	if (!dup)
		return NULL;
	memcpy(dup, s, len);
	dup[len] = '\0';
	return dup;
}
