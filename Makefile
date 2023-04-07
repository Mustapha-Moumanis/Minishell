NAME = minishell

SRCS = main.c

PFILES = parser.c lexer.c

EFILES = execution.c

SRCS := $(addprefix src/, $(SRCS)) 

PFILES := $(addprefix src/parsing/, $(PFILES)) 

EFILES := $(addprefix src/execution/, $(EFILES))

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror  -lreadline -I $(HOME)/.brew/Cellar/readline/8.2.1/include \
								-L $(HOME)/.brew/Cellar/readline/8.2.1/lib \

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
	@echo "clean all!"

re: fclean all

.PHONY : clean fclean bonus re all