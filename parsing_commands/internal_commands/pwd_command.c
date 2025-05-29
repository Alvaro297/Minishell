/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-26 18:31:46 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-26 18:31:46 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_pwd(t_minishell *minishell)
{
	char	*cwd;
	char	*env_pwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		env_pwd = get_env_value(minishell->env_vars, "PWD", false);
		if (env_pwd)
			printf("%s\n", env_pwd);
		else
			perror("minishell: pwd");
		if (env_pwd)
			return (0);
		else
			return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
