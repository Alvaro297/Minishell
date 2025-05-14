
#include "libft.h"

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (!new_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
	free(ptr);
	return (new_ptr);
}
