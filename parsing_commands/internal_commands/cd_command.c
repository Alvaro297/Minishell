# include "../../minishell.h"

int		handle_cd(t_minishell *minishell)
{
	char	*path;
	char	*cwd;

	if (args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	path = ft_strdup(minishell->parsed_input[1]);
	if (!path)
		path = get_env_value(minishell->env_vars, "HOME");
	if (!path)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (chdir(path) != 0) {
		perror("minishell: cd");
		return (1);
	}
	set_env(&minishell->env_vars, "OLDPWD", getenv("PWD"));
	cwd = getcwd(NULL, 0);
	set_env(&minishell->env_vars, "PWD", cwd);
	free(cwd);
	return (0);
}
