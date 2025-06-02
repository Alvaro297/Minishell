SRC = 		cmds/cmd.c env_recharge/envp.c env_recharge/envp2.c env_recharge/envp3.c \
			error_control/check_archives.c error_control/check_syntax.c \
			error_control/error_control.c  error_control/controled_errors_parsing.c \
			error_control/controled_errors_parsing2.c fill_minishell/fill_minishell.c \
			fill_minishell/expand_variable.c fill_minishell/outfile_array.c \
			fill_minishell/quote_variable.c free_minishell/free_double_array.c \
			fill_minishell/get_history_file.c free_minishell/free_export.c \
			fill_minishell/expand_variable2.c fill_minishell/set_special_var.c fill_minishell/quote_printf_here_doc.c \
			history/load_history.c init_minishell/init_minishell.c \
			parsing_commands/internal_commands/export/export_command.c \
			parsing_commands/internal_commands/export/export_commands2.c \
			parsing_commands/internal_commands/export/print_entorn_variable.c \
			parsing_commands/internal_commands/cd_command.c \
			parsing_commands/internal_commands/echo_command.c \
			parsing_commands/internal_commands/env_command.c \
			parsing_commands/internal_commands/pwd_command.c \
			parsing_commands/internal_commands/unset_command.c \
			parsing_commands/internal_commands/exit_command.c \
			parsing_commands/command_type.c parsing_input/checker_args.c \
			parsing_input/parsing_cmd.c parsing_input/parsing_cmd2.c \
			parsing_input/parsing_cmd3.c parsing_input/parsing_cmd_split_modified.c \
			parsing_input/here_doc_parsing.c parsing_input/process_redirections.c \
			parsing_input/process_redirection2.c \
			signals/handle_sig.c main.c free_minishell.c \
			delete_quotes/delete_quotes.c delete_quotes/delete_quotes2.c \
			pipex/pipex.c pipex/utils.c pipex/libutils.c \
			pipex/ft_split.c pipex/ft_fd.c pipex/utils2.c \
			pipex/execute.c pipex/here_doc.c pipex/here_doc2.c pipex/here_doc3.c \
			pipex/execute2.c \
			pipex/no_pipes.c


NAME = minishell

RM = rm -rf

CC = gcc 

CFLAGS = -Wall -Wextra -Werror
VALGRIND_VALE	:=	./supp/new_supp.supp
VFLAGS			:=	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=$(VALGRIND_VALE)

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

valgrind: re
	valgrind $(VFLAGS) ./$(NAME)

re: fclean all

all: $(NAME)
