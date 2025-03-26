# include "../minishell.h"

static bool	is_redirection_char(char c)
{
    return (c == '<' || c == '>');
}

static int	calculate_processed_size(char **command_splited)
{
    int	total_size;
    int	i;
    int	j;

    total_size = 0;
    i = 0;
    while (command_splited[i])
    {
        j = 0;
        while (command_splited[i][j])
        {
            if (is_redirection_char(command_splited[i][j]))
            {
                total_size++;
                if (command_splited[i][j + 1] && command_splited[i][j] == command_splited[i][j + 1])
                    j++;
                j++;
            }
            else
            {
                while (command_splited[i][j] && !is_redirection_char(command_splited[i][j]))
                    j++;
                total_size++;
            }
        }
        i++;
    }
    return (total_size);
}

static char	**split_redirection(char *token)
{
    char	**result;
    int		i;
    int		j;
    int		k;
    int		count;
    t_quotes quotes;

    quotes.in_single_quote = false;
    quotes.in_double_quote = false;

    // Contar cuántos tokens se generarán
    count = 0;
    i = 0;
    while (token[i])
    {
        // Actualizar el estado de las comillas
        if (token[i] == '\'' && !quotes.in_double_quote)
            quotes.in_single_quote = !quotes.in_single_quote;
        else if (token[i] == '"' && !quotes.in_single_quote)
            quotes.in_double_quote = !quotes.in_double_quote;

        if (is_redirection_char(token[i]) && !quotes.in_single_quote && !quotes.in_double_quote)
        {
            count++;
            if (token[i + 1] && token[i] == token[i + 1]) // Redirección doble (<< o >>)
                i++;
        }
        else
        {
            while (token[i] && (!is_redirection_char(token[i]) || quotes.in_single_quote || quotes.in_double_quote))
                i++;
            count++;
        }
        i++;
    }

    // Reservar memoria para los tokens
    result = malloc(sizeof(char *) * (count + 1));
    if (!result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Dividir el token en partes
    i = 0;
    k = 0;
    while (token[i])
    {
        // Actualizar el estado de las comillas
        if (token[i] == '\'' && !quotes.in_double_quote)
            quotes.in_single_quote = !quotes.in_single_quote;
        else if (token[i] == '"' && !quotes.in_single_quote)
            quotes.in_double_quote = !quotes.in_double_quote;

        if (is_redirection_char(token[i]) && !quotes.in_single_quote && !quotes.in_double_quote)
        {
            j = i;
            if (token[i + 1] && token[i] == token[i + 1]) // Redirección doble
                i += 2;
            else
                i++;
            result[k++] = ft_strndup(token + j, i - j);
        }
        else
        {
            j = i;
            while (token[i] && (!is_redirection_char(token[i]) || quotes.in_single_quote || quotes.in_double_quote))
                i++;
            result[k++] = ft_strndup(token + j, i - j);
        }
    }
    result[k] = NULL;
    return (result);
}

bool	is_valid_redirection(char *token, t_quotes *quotes)
{
    int	i;

    i = 0;
    while (token[i])
    {
        if (token[i] == '\'' && !quotes->in_double_quote)
            quotes->in_single_quote = !quotes->in_single_quote;
        else if (token[i] == '"' && !quotes->in_single_quote)
            quotes->in_double_quote = !quotes->in_double_quote;
        if (is_redirection_char(token[i]) && !quotes->in_single_quote && !quotes->in_double_quote)
            return (true);

        i++;
    }
    return (false);
}

char	**process_redirection(char **command_splited)
{
    char	**processed;
    int		i;
    int		j;
    int		total_size;
    t_quotes quotes;

    quotes.in_single_quote = false;
    quotes.in_double_quote = false;
    total_size = calculate_processed_size(command_splited);
    processed = malloc(sizeof(char *) * (total_size + 1)); 
    if (!processed)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    i = 0;
    j = 0;
    while (command_splited[i])
    {
        if (is_valid_redirection(command_splited[i], &quotes))
        {
            char **split = split_redirection(command_splited[i]);
            int k = 0;
            while (split[k])
                processed[j++] = split[k++];
            free(split);
        }
        else
            processed[j++] = ft_strdup(command_splited[i]);
        i++;
    }
    processed[j] = NULL;
    return (processed);
}
