#include  "../../minishell.h"

static char	*parsed_variable_name(char *str)
{
	char	*equal_pos;
	char	*var_name;
	size_t	name_len;
	
	equal_pos = ft_strchr(str, '=');
	if (equal_pos != NULL) {
		name_len = equal_pos - input;
		var_name = malloc(name_len + 1);
		ft_strncpy(var_name, input, name_len);
		var_name[name_len] = '\0';
	}
	return (var_name);
}

static bool	parsed_name_export(char *str, char *var_name)
{
	char	*var_value;

	var_value = ft_strchr(str, '=');
	
}

int		handle_export(t_minishell *minishell, char **envp)
{
	int		i;
	char	*var_name;
	char	*var_check;

	i = 1;
	while (minishell->parsed_input[i])
	{
		var_name = parsed_variable_name(minishell->parsed_input[i]);
		var_check = ft_strchr(minishell->parsed_input[i], '=');
		if (var_check != NULL && *(var_check + 1) != '\0' &&
			minishell->parsed_input[i][0] != '=')
		{
			if (parsed_name_export(minishell->parsed_input[i], var_name))
			{
				/* code */
			}
		}
	}
}
