#include  "../../../minishell.h"

static char	*parsed_variable_name(char *str)
{
	char	*equal_pos;
	char	*var_name;
	size_t	name_len;
	
	equal_pos = ft_strchr(str, '=');
	if (equal_pos != NULL) {
		name_len = equal_pos - str;
		var_name = malloc(name_len + 1);
		ft_strlcpy(var_name, str, name_len);
		var_name[name_len] = '\0';
	}
	return (var_name);
}

static bool parsed_value_validation(char *var_value)
{
	int i;
	int j;

	i = 0;
	if (ft_isdigit(var_value[i]))
		return (false);
	if ((var_value[i] == '\'' && var_value[ft_strlen(var_value) - 1] == '\'') ||
		(var_value[i] == '"' && var_value[ft_strlen(var_value) - 1] == '"'))
		return (true);
	else
	{
		while (var_value[i])
		{
			j = 0;
			while (INVALID_CHARACTERSV[j])
			{
				if (INVALID_CHARACTERSV[j] == var_value[i])
					return (false);
				j++;
			}
			i++;
		}
	}
	return (true);
}

static bool parsed_name_validation(char *var_name)
{
	int i;
	int j;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return false;
	while (var_name[i])
	{
		j = 0;
		while (INVALID_CHARACTERS[j])
		{
			if (INVALID_CHARACTERS[j] == var_name[i])
				return false;
			j++;
		}
		i++;
	}
	return true;
}

int		handle_export(t_minishell *minishell)
{
	int		i;
	char	*var_name;
	char	*var_check;

	i = 0;
	while (minishell->cmds->args[++i] && !minishell->cmds->is_pipe)
	{
		var_name = parsed_variable_name(minishell->cmds->args[i]);
		var_check = ft_strchr(minishell->cmds->args[i], '=');
		if (var_check != NULL && *(var_check + 1) != '\0' &&
			minishell->cmds->args[i][0] != '=')
		{
			var_check++;
			if (parsed_name_validation(var_name) && parsed_value_validation(var_check))
				set_env(&minishell->env_vars, var_name, var_check);
		}
		else if (var_check == NULL && var_name != NULL)
			if (parsed_name_validation(var_name))
				set_env(&minishell->env_vars, var_name, "");
	}
	if (minishell->cmds->is_pipe && minishell->cmds->args[1])
		minishell->output = ft_strdup("");
	if (i == 1 && !minishell->cmds->args[1])
		print_entorn_variable(minishell);
	return (0);
}
