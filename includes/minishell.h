/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/04/09 07:23:50 by mmoumani         ###   ########.fr       */
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
#define TOKEN_ERROR 6
#define TOKEN_APPEND 7
#define TOKEN_END 99

typedef struct s_cmd
{
	char			**in_file;
	char			**out_file;
	char			**full_cmd;
	struct s_cmd	*next;
}					t_cmd;

// typedef struct s_cmd
// {
//     char			*content;
//     int			type;
//     struct s_cmd	*next;
// }       t_cmd;

// DATA :

typedef struct s_data
{
	t_cmd	*head;
	char	*input;
	int		ac;
	char	**av;
	char	**env;
}			t_data;

// PARSING :

typedef struct s_token
{
	char	*value;
	int		type;
	char	*error;
}			t_token;

typedef struct s_lexer
{
	char	*input;
	int		size;
	int		position;
}			t_lexer;

void	parser(t_data *data);
int		check(t_data *data);

// more function

int		ft_whitespace(int c);

// lexer function

void	lexer(t_data *data);
void	lexer_read_cmd_quote(t_lexer *lexer, t_token *token);
void	lexer_read_cmd(t_lexer *lexer, t_token *token);

// linkedlist function

t_cmd	*ft_lst_new(char **in_file, char **out_file, char **full_cmd);
t_cmd	*ft_lst_last(t_cmd *lst);
void	ft_lst_back(t_cmd **lst, t_cmd *new);

// EXECUTION :

void	exuct(t_data *data);

#endif