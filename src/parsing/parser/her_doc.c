/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:47:06 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/24 16:21:47 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_new_name(int fd)
{
	char	*name;
	char	c;
	int		i;
	int		ret;

	name = malloc(9 * sizeof(char));
	fd = open("/dev/random", O_RDONLY);
	if (!name || fd < 0)
		return (NULL);
	ret = 0;
	i = 0;
	while (i < 8)
	{
		ret = read(fd, &c, 1);
		if (ret == -1)
			return (NULL);
		if (ft_isalpha(c))
			name[i++] = c;
	}
	name[i] = '\0';
	close(fd);
	return (name);
}

int	her_doc(t_data *data, t_elem **lex, char *value)
{
	char	*str;
	char	*tmp;
	char	*name;
	int		ret;

	str = NULL;
	ret = 0;
	name = get_new_name(data->in);
	if (data->in > 2)
		close(data->in);
	data->in = open(name, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (data->in < -1)
		return (0);
	while (1337)
	{
		str = get_next_line(1);
		if (str && str[0] != '\n')
		{
			tmp = ft_strtrim(str, "\n");
			if (ft_strcmp(tmp, value))
			{
				if ((*lex) && (*lex)->type == ENV)
					ft_putstr_fd("ok", data->in);
				else
					write(data->in, str, ft_strlen(str));
			}
			else
			{
				free(str);
				free(tmp);
				break ;
			}
			free(tmp);
		}
		free(str);
	}
	close(data->in);
	data->in = open(name, O_RDONLY, 0644);
	free(name);
	return (1);
}
