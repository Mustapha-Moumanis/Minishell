/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:52:47 by shilal            #+#    #+#             */
/*   Updated: 2023/04/05 01:05:20 by mmoumani         ###   ########.fr       */
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

// DATA :

typedef struct s_data
{
	t_list	*head;
	char	**env;
	char	*input;
	char	**in_file;
	char	**out_file;
	char	**cmd;
	char	**var;
	char	**s;
	int		s_quote;
	int		d_quote;
	int		is_var;
}			t_data;

// PARSING :

typedef struct s_token {
	char*	value;
	int		type;
	int		size;
}			Token;

typedef struct s_lexer {
	char* 	input;
	int		size;
	int 	position;
}       Lexer;

void	parser(t_data *data);
int	    check(t_data *data);
int		ft_whitespace(int c);
int		lexer_parsing(t_data *data);



// EXECUTION :

void	exuct(t_data *data);

#endif