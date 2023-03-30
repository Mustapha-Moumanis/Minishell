/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:29:04 by mmoumani          #+#    #+#             */
/*   Updated: 2022/11/06 22:09:31 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	b;

	b = (char)c;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == b)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
