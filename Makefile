NAME = minishell

SRCS = main.c

PFILES = parser.c lexer/lexer.c lexer/ft_elemlst.c syntax_errors.c parsing.c parse_utils.c redirection.c cmd_lst.c append.c

EFILES = execution.c utils_2.c utils_1.c exec.c

BUILTINS = echo.c pwd.c env.c cd.c export.c utils_export.c unset.c

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