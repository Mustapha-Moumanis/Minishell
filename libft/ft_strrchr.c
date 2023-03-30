/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:30:46 by mmoumani          #+#    #+#             */
/*   Updated: 2022/11/01 01:15:14 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		j;
	char	m;
	size_t	len;

	i = 0;
	j = -1;
	m = c;
	len = ft_strlen(s);
	if (m == s[len])
		return ((char *)&s[len]);
	while (s[i])
	{
		if (s[i] == m)
			j = i;
		if (s[i + 1] == '\0' && j != -1)
			return ((char *)&s[j]);
		i++;
	}
	return (NULL);
}
