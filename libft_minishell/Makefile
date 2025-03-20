#Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
NAME = libft.a
SRCS = ft_isalnum.c ft_isalpha.c ft_isprint.c ft_isascii.c ft_isdigit.c ft_tolower.c ft_toupper.c ft_bzero.c ft_calloc.c ft_memchr.c\
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strdup.c ft_strndup.c ft_atoi.c ft_itoa.c ft_split.c ft_strchr.c ft_striteri.c\
	ft_strjoin.c ft_strjoin_free.c ft_strlcat.c ft_strncpy.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_realloc.c get_next_line.c
SRCB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
	ft_lstmap.c
OBJ = $(SRCS:.c=.o)
BONUSOBJ = $(SRCB:.c=.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ) $(BONUSOBJ)
fclean: clean
	$(RM) $(NAME)
bonus: $(OBJ) $(BONUSOBJ)
	ar rc $(NAME) $(OBJ) $(BONUSOBJ)
re: fclean all