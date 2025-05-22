# include "../minishell.h"

char	*get_history_file(void)
{
	char	cwd[PATH_MAX];
	char	*history_file;
	size_t	len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		fprintf(stderr, "Error: Can't get current directory for history file.\n");
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
