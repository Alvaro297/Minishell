# include "../minishell.h"

void signals_ignore(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN; // Ignorar la señal
	sa.sa_flags = SA_RESTART; // O 0, SA_RESTART no es tan relevante para SIG_IGN
	sigemptyset(&sa.sa_mask); // Limpiar máscara de señales bloqueadas durante el handler
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

void	manage_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	manage_signals_heredoc(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint_heredoc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}