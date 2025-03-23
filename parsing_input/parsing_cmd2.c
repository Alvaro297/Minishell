/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 17:56:35 by alvamart          #+#    #+#             */
/*   Updated: 2025-02-07 17:56:35 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

static bool	is_redirected(char *command_splited)
{
    if ((ft_strncmp(command_splited, "<", 1) == 0 ||
            ft_strncmp(command_splited, ">", 1) == 0 ||
            ft_strncmp(command_splited, ">>", 2) == 0) &&
            ft_strlen(command_splited) <= 2)
            return (true);
    return (false);
}

char	*find_command(char **command_splited)
{
    int		i;

    i = 0;
    while (command_splited[i])
    {
        if (is_redirected(command_splited[i]))
        {
            i++;
            if (is_redirected(command_splited[i]))
                return (NULL);
            i++;
        }
        else
        {
            printf("find_command: command found: %s\n", command_splited[i]);
            return (command_splited[i]);
        }
    }
    return (NULL);
}

static char	**find_args_help(char **command_splited, int count)
{
    char	**args;
    int		i;
    int		j;

    i = 0;
    j = 0;
    args = malloc((count + 1) * sizeof(char *));
    if (!args)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while (command_splited[i])
    {
        if (is_redirected(command_splited[i]))
            i++;
        else
        {
            args[j] = ft_strdup(command_splited[i]);
            printf("find_args_help: arg[%d] = %s\n", j, args[j]);
            j++;
        }
        i++;
    }
    args[j] = NULL;
    return (args);
}

char	**find_args(char **command_splited)
{
    int		i;
    int		count;
    
    count = 0;
    i = 0;
    while (command_splited[i])
    {
        if (is_redirected(command_splited[i]))
            i++;
        else
            count++;
        i++;
    }
    printf("find_args: total args count = %d\n", count);
    return (find_args_help(command_splited, count));
}