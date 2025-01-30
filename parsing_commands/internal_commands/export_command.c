#include  "../../minishell.h"

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
			var_check++;
			if (parsed_name_validation(var_name) && parsed_value_validation(var_check))
				set_env(&minishell->env_vars, var_name, var_check);
		}
		else if (var_check == NULL && var_name != NULL)
			if (parsed_name_validation(var_name))
				set_env(&minishell->env_vars, var_name, "");
	}
	if (i == 1)
		print_entorn_variable(minishell); // Hay que hacer una funcion en la cual si solo le pasas (export) a la mini te ponga ALPHABETICAMENTE
										  // TODAS las variables de entorno. Incluso las que se han creado. Si la variable de entorno necesita "" se ponen y sino no
										  // incluso si se han creado con ella EJ: export HOLA="hola" se mostrara como define -x HOLA=hola
	return (1);
}
