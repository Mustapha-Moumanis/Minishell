/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/05/16 15:37:22 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
#include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

// Define token types as constants
# define TOKEN_IN_FILE 1
# define TOKEN_OUT_FILE 2
# define TOKEN_HD 3
# define TOKEN_PIPE 4
# define TOKEN_COMMAND 5
# define TOKEN_APPEND 7
# define TOKEN_END 99

typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	char			p;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char	*value;
	int		size;
	int		type;
}			t_token;

typedef struct s_lexer
{
	char	*input;
	int		error;
	int		in_file;
	int		position;
}			t_lexer;

// DATA :

typedef struct s_data
{
	t_cmd	*head;
	char	*input;
	char	**env;
	int		error;
	t_list	*cmd_lst;
	int		n_cmd;
	int		in;
	int		out;
}			t_data;

// Data of execution part :

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*name;
	char			sep;
	char			*value;
	struct s_export	*next;
}					t_export;

typedef struct s_exec
{
	int			i;
	int			size;
	char		*check;
	char		cd_path[1024];
	char		last_path[1024];
	char		old_path[1024];
	int			len_path;
	int			pos_path;
	int			onther;
	char		**n_env;
	t_cmd		*tmp;
	t_env		*env;
	t_export	*export;
}				t_exec;

// PARSING :

int		parser(t_data *data);
void	append_exution_struct(t_data *data);
void	init_parssing_data(t_data *data);
void	check_in_file(t_data *data, t_lexer *lexer, t_token *token);
void	check_out_file(t_data *data, t_lexer *lexer, t_token *token);
void	check_append_file(t_data *data, t_lexer *lexer, t_token *token);

// more function

int		ft_whitespace(int c);
void	ft_double_free(char **s);

// lexer function

void	lexer(t_data *data);
void	lexer_read_cmd_quote(t_lexer *lexer, t_token *token);
void	lexer_read_cmd(t_lexer *lexer, t_token *token);

// linkedlist function

t_cmd	*ft_lst_new(int in_file, int out_file, char **full_cmd);
t_cmd	*ft_lst_last(t_cmd *lst);
void	ft_lst_back(t_cmd **lst, t_cmd *new);
void	ft_lst_clear(t_cmd **lst, void (*del)(char **));

// EXECUTION :

void	exuct(t_data *data, t_exec *val);
void	ecx(char **av, char **en);
void	builtins(t_exec *val);
void	sp_builtins(t_exec *val);

// UTILS :
int	add_value_export(t_exec *val, char *n, char *v);
void	change_path(t_exec *val, char *str, char *value);
void	decrement_path(t_exec *val);
void	export_error(char *str);
void	print_export(t_exec *val);
t_env	*new_env(char *name, char *value);
t_export	*new_export(char *name, char *value, char sep);
void	ft_lenked_list(char **env, t_exec *val);
int		ft_strcmp(char *s1, char *s2);
void	str_lowercase(char *str);
t_env	*ft_lstlast_env(t_env *lst);
void	add_env(t_env **lst, t_env *new);
t_export	*ft_lstlast_export(t_export *lst);
t_env	*ft_lstlast_env(t_env *lst);
void	add_export(t_export **lst, t_export *new);
char	*value(char *str);
char	*name(char *str);
int	ft_lstsize_h(t_cmd *lst);
char	**list_to_table_h(t_env **lst);

//  BUILTINS :

void	export(t_exec *val);
void	echo(t_exec *val);
void	env(t_exec *val);
void	cd(t_exec *val);
void	pwd(t_exec *val);
void	unset(t_exec *val);

#endif