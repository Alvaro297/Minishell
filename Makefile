SRC = 		cmds/cmd.c env_recharge/envp.c env_recharge/envp2.c \
			error_control/check_archives.c error_control/check_syntax.c \
			error_control/error_control.c fill_minishell/fill_minishell.c \
			fill_minishell/expand_variable.c fill_minishell/outfile_array.c \
			fill_minishell/quote_variable.c free_minishell/free_double_array.c \
			history/load_history.c \
			parsing_commands/internal_commands/export/export_command.c \
			parsing_commands/internal_commands/export/print_entorn_variable.c \
			parsing_commands/internal_commands/cd_command.c \
			parsing_commands/internal_commands/echo_command.c \
			parsing_commands/internal_commands/env_command.c \
			parsing_commands/internal_commands/pwd_command.c \
			parsing_commands/internal_commands/unset_command.c \
			parsing_commands/command_type.c parsing_input/checker_args.c \
			parsing_input/parsing_cmd.c parsing_input/parsing_cmd2.c \
			parsing_input/parsing_cmd3.c parsing_input/parsing_cmd_split_modified.c \
			signals/handle_sig.c main.c \
			delete_quotes/delete_quotes.c \
			pipex/pipex.c pipex/utils.c pipex/libutils.c \
			pipex/ft_split.c pipex/ft_fd.c pipex/utils2.c

NAME = Minishell

RM = rm -rf

CC = gcc 

CFLAGS = -Wall -Wextra -Werror 

LIBFT = libft_minishell/

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@make -sC libft_minishell/
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)libft.a -lreadline

clean:
	$(RM) $(OBJ)
	make clean -sC $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFTPATH)
	make clean -sC $(LIBFT) 

re: fclean all

all: $(NAME)