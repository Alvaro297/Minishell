/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-28 19:03:42 by alvamart          #+#    #+#             */
/*   Updated: 2025-05-28 19:03:42 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_history_file(void)
{
	char	cwd[PATH_MAX];
	char	*history_file;
	size_t	len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("Error: Can't get current directory for file.\n", 2);
		return (NULL);
	}
	len = ft_strlen(cwd) + ft_strlen("/minishell_history") + 1;
	history_file = malloc(len);
	if (!history_file)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strlcpy(history_file, cwd, len);
	ft_strlcat(history_file, "/minishell_history", len);
	return (history_file);
}
