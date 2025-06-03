/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:56:28 by paperez-          #+#    #+#             */
/*   Updated: 2025/06/03 16:56:31 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_signal = 130;
}

int	heredoc_event_hook(void)
{
	if (g_signal == 130)
		rl_done = 1;
	return (0);
}

void	process_heredoc_signals(struct sigaction *sa_old,
		struct sigaction *sa_new)
{
	sigaction(SIGINT, NULL, sa_old);
	sa_new->sa_handler = sigint_heredoc_handler;
	sigemptyset(&sa_new->sa_mask);
	sa_new->sa_flags = 0;
	sigaction(SIGINT, sa_new, NULL);
}
