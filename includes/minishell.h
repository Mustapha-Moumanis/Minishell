/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/04/12 21:01:52 by mmoumani         ###   ########.fr       */
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
#define TOKEN_IN_FILE 1
#define TOKEN_OUT_FILE 2
#define TOKEN_HD 3
#define TOKEN_PIPE 4
#define TOKEN_COMMAND 5
#define TOKEN_APPEND 7
#define TOKEN_END 99

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
	int		ac;
	char	**av;
	char	**env;
	t_lexer	lexer;
	t_token	token;
	t_list	*cmd_lst;
	int		n_cmd;
	int		in;
	int		out;
}			t_data;

// PARSING :

void	parser(t_data *data);
int		check(t_data *data);
void	append_exution_struct(t_data *data);

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

void	exuct(t_data *data);

#endif