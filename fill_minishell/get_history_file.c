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
	char		*home;
	char		*history_file;
	size_t		len;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("Error: HOME not set for history file.\n", 2);
		return (NULL);
	}
	len = ft_strlen(home) + ft_strlen("/minishell_history") + 1;
	history_file = malloc(len);
	if (!history_file)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strlcpy(history_file, home, len);
	ft_strlcat(history_file, "/minishell_history", len);
	return (history_file);
}
