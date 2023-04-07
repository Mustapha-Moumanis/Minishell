/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/04/06 21:22:10 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include "../libft/libft.h"

typedef struct s_cmd
{
	char			**in_file;
	char			**out_file;
	char			**full_cmd;
	char			**var;
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
	char	**env;
	char	*input;
}			t_data;

// PARSING :

typedef struct s_token {
	char*	value;
	int		type;
}			Token;

typedef struct s_lexer {
	char* 	input;
	int		size;
	int 	position;
}       Lexer;

void	parser(t_data *data);
int	    check(t_data *data);
int		ft_whitespace(int c);
void	lexer(t_data *data);



// EXECUTION :

void	exuct(t_data *data);

#endif