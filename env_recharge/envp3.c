/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 15:29:52 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 15:29:52 by alvamart         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_shlvl(void)
{
	char	*shlvl;
	int		shlvl_value;

	shlvl = getenv("SHLVL");
	if (shlvl)
	{
		shlvl_value = ft_atoi(shlvl) + 1;
		return (ft_itoa(shlvl_value));
	}
	return (ft_strdup("1"));
}

t_env	*init_env_without_env(void)
{
	t_env	*head;
	char	cwd[1024];

	head = NULL;
	set_env(&head, "SHLVL", init_shlvl());
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env(&head, "PWD", cwd);
		set_env(&head, "OLDPWD", cwd);
	}
	set_env(&head, "HOME", "/");
	set_env(&head, "PATH", "");
	set_env(&head, "_", "");
	set_env(&head, "?", "0");
	return (head);
}
