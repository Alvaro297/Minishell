#include "../minishell.h"

void sigint_heredoc_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(1);
}

int process_heredoc(const char *delimiter)
{
    char *line;
    int fd = open(TMP_HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    signal(SIGINT, sigint_heredoc_handler);

    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        dprintf(fd, "%s\n", line);
        free(line);
    }
    close(fd);
    return 0;
}

int handle_heredoc(const char *delimiter)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
    }

    if (pid == 0)
    {
        // Proceso hijo: captura input y escribe en archivo temporal
        if (process_heredoc(delimiter) < 0)
            exit(1);
        exit(0);
    }
    else
    {
        // Proceso padre: espera al hijo y abre el archivo para lectura
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
        {
            unlink(TMP_HEREDOC);
            return (-1);
        }
        int fd = open(TMP_HEREDOC, O_RDONLY);
        unlink(TMP_HEREDOC); // Eliminamos el archivo después de abrirlo
        if (fd < 0)
        {
            perror("open heredoc");
            return (-1);
        }
        return (fd);
    }
}
