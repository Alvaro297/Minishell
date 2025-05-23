# include "../minishell.h"

void	handle_unclosed_quotes(t_minishell *minishell, t_quotes quotes, char **result)
{
	set_special_var_inputNull(minishell, *result);
	free(*result);
	*result = NULL;
	if (quotes.in_single_quote)
		write(2, "minishell: unclosed single quote\n", 34);
	else
		write(2, "minishell: unclosed double quote\n", 34);
	set_env(&minishell->env_vars, "?", "2");
}