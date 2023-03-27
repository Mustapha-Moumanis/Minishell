NAME = minishell

SRCS = main.c check.c

UTLS = libft/ft_split.c libft/ft_strlen.c libft/ft_substr.c libft/ft_strdup.c

RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror -I /goinfre/shilal/homebrew/Cellar/readline/8.2.1/include -lreadline

all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(UTLS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY : clean fclean re bonus all