#include "../minishell.h"

void	free_double_aray(void **double_array)
{
	int	i;

	i = 0;
	if (!double_array)
		return ;
	while (double_array[i])
		free(double_array[i]);
	free(double_array);
}
