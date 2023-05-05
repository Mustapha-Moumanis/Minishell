NAME = minishell

SRCS = main.c

PFILES = parser.c lexer.c ft_lexer_1.c ft_lst.c append.c check_file.c

EFILES = execution.c utils_exec.c builtins_utils.c

BUILTINS = echo.c pwd.c env.c cd.c export.c

SRCS := $(addprefix src/, $(SRCS)) 

PFILES := $(addprefix src/parsing/, $(PFILES)) 

EFILES := $(addprefix src/execution/, $(EFILES))

BUILTINS := $(addprefix src/execution/Builtins/, $(BUILTINS))

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror -lreadline -I $(HOME)/.brew/Cellar/readline/8.2.1/include \
								-L $(HOME)/.brew/Cellar/readline/8.2.1/lib \
# -fsanitize=address -g
all: $(NAME)

$(NAME) : $(SRCS) $(PFILES) $(EFILES) $(BUILTINS)
	@make -C libft
	@$(CC) $(CFLAGS) libft/libft.a $(SRCS) $(PFILES) $(EFILES) $(BUILTINS) -o $(NAME)
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