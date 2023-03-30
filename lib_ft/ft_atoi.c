/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:04:21 by mmoumani          #+#    #+#             */
/*   Updated: 2022/12/23 21:12:08 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_white_space(const char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	r;

	i = 0;
	sign = 1;
	r = 0;
	i = ft_white_space(str, i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r *= 10;
		r += (str[i] - '0');
		if ((r > 9223372036854775807) && (sign == 1))
			return (-1);
		if ((r > 9223372036854775807) && (sign == -1))
			return (0);
		i++;
	}
	return (r * sign);
}
