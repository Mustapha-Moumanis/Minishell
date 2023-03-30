/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 01:40:28 by mmoumani          #+#    #+#             */
/*   Updated: 2022/11/04 20:11:36 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(long n)
{
	int	i;

	i = 1;
	if (n < 0)
		n *= (-1);
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*negative_itoa(int nlen, long nlong, char *r)
{
	r = malloc((nlen + 2) * sizeof(char));
	if (!r)
		return (NULL);
	r[nlen + 1] = '\0';
	nlong *= (-1);
	while (nlen)
	{
		r[nlen] = (nlong % 10) + 48;
		nlong /= 10;
		nlen--;
	}
	r[nlen] = '-';
	return (r);
}

static char	*positive_itoa(int nlen, long nlong, char *r)
{
	r = malloc((nlen + 1) * sizeof(char));
	if (!r)
		return (NULL);
	r[nlen] = '\0';
	while (nlen)
	{
		r[nlen - 1] = (nlong % 10) + 48;
		nlong /= 10;
		nlen--;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	int		nlen;
	long	nlong;
	char	*r;

	r = NULL;
	nlong = (long)n;
	nlen = ft_nlen(n);
	if (nlong < 0)
		r = negative_itoa(nlen, nlong, r);
	else
		r = positive_itoa(nlen, nlong, r);
	return (r);
}
