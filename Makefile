NAME = minishell

SRCS = main.c

PFILES = check.c parser.c

EFILES = main.c


SRCS := $(addprefix src/, $(SRCS)) 

PFILES := $(addprefix src/parsing/, $(PFILES)) 

EFILES := $(addprefix src/execution/, $(EFILES))

RM = rm -f
CC = cc

CFLAGS = -Wall -Wextra -Werror -I /goinfre/shilal/homebrew/Cellar/readline/8.2.1/include -lreadline
# CFLAGS = -Wall -Wextra -Werror -L ~/goinfre/mmoumani/homebrew/Cellar/readline/8.2.1/readline/lib/libreadline.a -I ~/goinfre/mmoumani/homebrew/Cellar/readline/8.2.1/include -lreadline

all: $(NAME)

$(NAME) : $(SRCS)
	@$(MAKE) -C libft all
	@$(CC) $(CFLAGS) libft/libft.a $(SRCS) $(PFILES) -o $(NAME)

clean:
	$(RM) $(NAME) libft/*.o

fclean: clean
	$(RM) libft/*.a

re: fclean all

.PHONY : clean fclean bonus re all