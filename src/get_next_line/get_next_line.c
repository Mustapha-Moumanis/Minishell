/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:51:20 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/23 18:12:11 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_reserve(char *re, char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = ft_strlen(line);
	j = ft_strlen(re) + 1;
	tmp = malloc(j - i);
	if (!tmp)
		return (NULL);
	j = 0;
	while (re[i])
	{
		tmp[j] = re[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(re);
	return (tmp);
}

char	*ft_add_in_reserve(char *reserve, int fd)
{
	char	*buf;
	int		ret;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!(ft_strchr(reserve, '\n')))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0)
			break ;
		if (ret == -1)
		{
			free(buf);
			free(reserve);
			return (NULL);
		}
		buf[ret] = '\0';
		reserve = ft_strjoin_2(reserve, buf);
	}
	free(buf);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve;
	char		*line;

	if (BUFFER_SIZE < 0)
		return (NULL);
	reserve = ft_add_in_reserve(reserve, fd);
	if (!reserve || reserve[0] == '\0')
	{
		free(reserve);
		reserve = NULL;
		return (NULL);
	}
	line = ft_first_str(reserve);
	reserve = ft_reserve(reserve, line);
	return (line);
}
