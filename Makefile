NAME = minishell

SRCS = main.c check.c parser.c

UTLS = 

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