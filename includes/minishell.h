/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/04/15 15:06:10 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <string.h>
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

typedef struct s_exec
{
	int		i;
	char	*check;
	char	cd_path[1024];
	char	last_path[1024];
	char	old_path[1024];
	int		len_path;
	int		pos_path;
	int		onther;
}				t_exec;

// PARSING :

int		parser(t_data *data);
void	append_exution_struct(t_data *data);
void	init_parssing_data(t_data *data);

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

void	exuct(t_cmd *cmd, t_data *data, t_exec *val);
int		ft_strcmp(char *s1, char *s2);

void	export(t_exec *val, t_data *data);
void	echo(t_exec *val, t_data *data);
void	env(t_exec *val, t_data *data);
void	cd(t_exec *val, t_data *data);
void	pwd(t_exec *val, t_data *data);

#endif