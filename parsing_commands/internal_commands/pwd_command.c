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

int	handle_pwd(t_cmd *current_cmd, t_minishell *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
