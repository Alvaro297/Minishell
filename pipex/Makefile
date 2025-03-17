SRC = pipex.c utils.c libutils.c ft_split.c ft_fd.c 

NAME = pipex

RM = rm -rf

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
 
%.o: %.c
	${CC} $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: $(clean)
	$(RM) $(NAME)
	$(RM) $(OBJ)

re: fclean all
