NAME = minishell

SRCS = main.c check.c parser.c

SRCS := $(addprefix src/, $(SRCS)) 

RM = rm -f
CC = cc

CFLAGS = -Wall -Wextra -Werror -I /goinfre/shilal/homebrew/Cellar/readline/8.2.1/include -lreadline
# CFLAGS = -Wall -Wextra -Werror -L ~/goinfre/mmoumani/homebrew/Cellar/readline/8.2.1/readline/lib/libreadline.a -I ~/goinfre/mmoumani/homebrew/Cellar/readline/8.2.1/include -lreadline

all: $(NAME)

$(NAME) : $(SRCS) 
	$(MAKE) -C libft all
	$(CC) $(CFLAGS) libft/libft.a $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME) libft/*.o

fclean: clean

re: fclean all

.PHONY : clean fclean bonus re all