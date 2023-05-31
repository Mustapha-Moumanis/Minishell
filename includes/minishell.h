/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/05/31 16:41:59 by mmoumani         ###   ########.fr       */
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
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_cmd
{
	int				in_file;
	int				out_file;
	char			**full_cmd;
	struct s_cmd	*next;
}					t_cmd;

// lexer 2 function

enum e_type
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DQUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	EXIT_STATUS,
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
	OR,
	AND
};

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL
};

typedef struct s_elem
{
	char			*content;
	enum e_type		type;
	enum e_state	state;
	struct s_elem	*next;
}					t_elem;

typedef struct s_lexer
{
	char	*input;
	int		len;
	int		position;
}			t_lexer;

typedef struct s_token
{
	char			*value;
	int				len;
	enum e_type		type;
	enum e_state	state;
}			t_token;

// DATA :

typedef struct s_data
{
	t_cmd			*head;
	char			*input;
	t_list			*cmd_lst;
	int				in;
	int				out;
	t_elem			*elem;
	int				error;
	int				file_error;
	t_list			*save_error;
	struct s_env	*n_env;
}			t_data;

int			g_exit_status;

// Data for execution part :

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
}					t_exprt;

typedef struct s_exec
{
	int			i;
	int			j;
	int			size;
	int			n_p;
	int			fork;
	int			**pe;
	char		*check;
	char		cd_path[1024];
	char		last_path[1024];
	char		old_path[1024];
	int			pos_path;
	char		**n_env;
	t_cmd		*tmp;
	t_env		*env;
	t_exprt		*export;
}				t_exec;

// PARSING : --------------------------

char	*parse_word(t_elem **lex);
int		parsing(t_data *data, t_elem *lex);
char	*parse_env(t_data *data, t_elem **lex);
char	*parse_cmd(t_data *data, t_elem **lex);
char	*parse_qoute(t_data *data, t_elem **lex, enum e_type type);

int		parser(t_data *data);
void	append_exution_struct(t_data *data);
void	init_parssing_data(t_data *data, int ac, char **av);

void	in_file(t_data *data, char *value);
void	out_file(t_data *data, char *value);
void	dout_file(t_data *data, char *value);

// HERE DOC

char	*get_delimiter(t_elem **lex, int *is);
char	*update_line(t_data *last_data, char *str);
int		her_doc(t_data *data, t_elem **lex, int var);
char	*get_qoute_delimiter(t_elem **lex, enum e_type type);

// more function

int		is_red(int c);
int		ft_quote(int c);
int		ft_whitespace(int c);
int		special_char(char c);
void	ft_double_free(char **s);
void	skeap_space(t_elem	**t);
void	print_error(t_list *list);
char	*cat_var(char *str, int nb);
int		initial_token(t_token *token, char c);
void	get_and(t_lexer *lexer, t_token *token);
void	get_word(t_lexer *lexer, t_token *token);
void	syntax_errors(t_data *data, t_elem	*t);
void	get_env(t_lexer *lexer, t_token *token, char first, char advance);

// lexer function

void	lexer(t_data *data);
void	get_pip(t_lexer *lexer, t_token *token);
void	get_infile_herdok(t_lexer *lexer, t_token *token);
void	get_outfile_append(t_lexer *lexer, t_token *token);
void	get_whitespace(t_lexer *lexer, t_token *token, char c);

// element function

t_elem	*ft_last_elem(t_elem *lst);
void	addback_elem(t_elem **lst, t_elem *new);
void	ft_delone_elem(t_elem *lst, void (*del)(void *));
void	ft_clear_elems(t_elem **lst, void (*del)(void *));
t_elem	*new_elem(char *content, enum e_type type, enum e_state state);

// cmd function

t_cmd	*ft_last_cmd(t_cmd *lst);
void	ft_cmd_back(t_cmd **lst, t_cmd *new);
void	ft_cmd_clear(t_cmd **lst, void (*del)(char **));
t_cmd	*ft_new_cmd(int in_file, int out_file, char **full_cmd);

// signale :

void	exc_sig(int sig);
void	exc_child_sig(int sig);

// EXECUTION : --------------------------

void	exuct(t_data *data, t_exec *val);
void	ecx(t_exec *val, char *path);
int		sp_builtins(t_exec *val);
int		builtins(t_exec *val);

// UTILS EXECUTION :
void	ft_lenked_list(char **env, t_exec *val);
void	ft_free_pipes(int **pipe, int size);
char	*my_strjoin_(char *s1, char *s2);
char	*get_path(t_env *env, char *str);
int		init_pipes(int size, int **pe);
char	**list_to_table_h(t_env **lst);
int		ft_strcmp(char *s1, char *s2);
void	ft_add_shlvl(t_exec *val);
void	str_lowercase(char *str);
int		ft_lstsize_h(t_cmd *lst);
int		exc_comande(t_exec *val);
int		one_cmd(t_exec *val);
void	dup_fd(t_exec *val);
void	wait_procces(void);
void	catch_signal(void);

//  BUILTINS :

void	ft_exit(t_exec *val);
void	export(t_exec *val);
void	unset(t_exec *val);
void	echo(t_exec *val);
void	pwd(t_exec *val);
void	env(t_exec *val);
int		cd(t_exec *val);

// UTILS BUILTINS :

void	change_path(t_exec *val, char *str, char *value);
void	add_value_env(t_exec *val, char *n, char *v);
t_exprt	*new_export(char *name, char *value, char sep);
void	add_export(t_exprt **lst, t_exprt *new);
int		all_iscorect(t_exec *val, char *str);
void	ft_check_add(t_exec *val, char *n);
t_env	*new_env(char *name, char *value);
void	add_env(t_env **lst, t_env *new);
t_exprt	*ft_lstlast_export(t_exprt *lst);
t_env	*ft_lstlast_env(t_env *lst);
t_env	*ft_lstlast_env(t_env *lst);
void	decrement_path(t_exec *val);
void	print_export(t_exec *val);
int		ft_lstsize_(t_env *lst);
char	*value(char *str);
char	*name(char *str);

// error :
int		export_error(char *str);
int		cd_error(char *obt, char *s);
int		ft_error(char *str);

#endif