/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shilal <shilal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:40:57 by shilal            #+#    #+#             */
/*   Updated: 2023/05/24 16:26:45 by shilal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fct_signal(int seg)
{
	(void)seg;
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("minishell : ", 1);
}

void	catch_signal(void)
{
	signal(SIGINT, &fct_signal);
}
