NAME = minishell

SRCS = main.c

PFILES = check.c parser.c



SRCS := $(addprefix src/, $(SRCS)) 

PFILES := $(addprefix src/parsing/, $(PFILES)) 

RM = rm -f
CC = cc

CFLAGS = -Wall -Wextra -Werror -I /goinfre/shilal/homebrew/Cellar/readline/8.2.1/include -lreadline
# CFLAGS = -Wall -Wextra -Werror -L ~/goinfre/mmoumani/homebrew/Cellar/readline/8.2.1/readline/lib/libreadline.a -I ~/goinfre/mmoumani/homebrew/Cellar/readline/8.2.1/include -lreadline

all: $(NAME)

$(NAME) : $(SRCS)
	$(MAKE) -C lib_ft all
	$(CC) $(CFLAGS) lib_ft/libft.a $(SRCS) $(PFILES) -o $(NAME)

clean:
	$(RM) $(NAME) lib_ft/*.o

fclean: clean
	$(RM) lib_ft/*.a

re: fclean all

.PHONY : clean fclean bonus re all