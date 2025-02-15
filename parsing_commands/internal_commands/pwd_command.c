# include "../../minishell.h"

int	handle_pwd(t_minishell *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	if (minishell->cmds->is_pipe)
		minishell->output = cwd;
	else
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}
