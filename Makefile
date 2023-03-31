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

all: $(NAME)

$(NAME) : $(SRCS) $(PFILES) $(EFILES)
	@make -C libft
	@$(CC) $(CFLAGS) libft/libft.a $(SRCS) $(PFILES) $(EFILES) -o $(NAME)
	@echo "Done!"

clean:
	@make clean -C libft
	@echo "clean!"

fclean:
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY : clean fclean bonus re all