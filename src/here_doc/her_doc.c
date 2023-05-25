/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:47:06 by mmoumani          #+#    #+#             */
/*   Updated: 2023/05/25 22:43:50 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_qoute_delimiter(t_elem **lex, enum e_type type)
{
	char	*s;
	char	*tmp;

	*lex = (*lex)->next;
	s = NULL;
	while (*lex)
	{
		if (!s)
			s = ft_strdup("");
		if ((*lex)->next && (*lex)->type == type && (*lex)->next->type == type)
			(*lex) = (*lex)->next;
		else if ((*lex)->type != type)
		{
			tmp = s;
			s = ft_strjoin(tmp, (*lex)->content);
			free(tmp);
		}
		else
			break ;
		if (*lex)
			*lex = (*lex)->next;
	}
	return (s);
}

char	*get_delimiter(t_elem **lex, int *is)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	skeap_space(lex);
	str = ft_strdup("");
	while (*lex && !ft_whitespace((*lex)->type) && (*lex)->type != '|')
	{
		tmp = str;
		if ((*lex)->type == DQUOTE || (*lex)->type == QOUTE)
		{
			tmp2 = get_qoute_delimiter(lex, (*lex)->type);
			str = ft_strjoin(tmp, tmp2);
			free(tmp2);
			*is = 1;
		}
		else
			str = ft_strjoin(tmp, (*lex)->content);
		free(tmp);
		if ((*lex)->next && is_red((*lex)->next->type))
			break ;
		(*lex) = (*lex)->next;
	}
	return (str);
}

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

char	*get_file(t_data *data)
{
	char	*path;
	char	*tmp;

	tmp = get_new_name(0);
	path = ft_strjoin("/tmp/", tmp);
	free(tmp);
	if (data->in > 2)
		close(data->in);
	data->in = open(path, O_CREAT | O_APPEND | O_RDWR, 0644);
	return (path);
}

int	append_line(t_data *data, char *str, char *value, int is)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strtrim(str, "\n");
	if (!ft_strcmp(tmp, value))
	{
		free(str);
		free(tmp);
		return (1);
	}
	if (is == 0)
	{
		tmp2 = update_line(data, tmp);
		ft_putstr_fd(tmp2, data->in);
		free(tmp2);
	}
	else
		ft_putstr_fd(str, data->in);
	free(tmp);
	return (0);
}

int	her_doc(t_data *data, t_elem **lex)
{
	char	*value;
	char	*path;
	char	*str;
	int		fd;
	int		is;

	is = 0;
	fd = data->in;
	value = get_delimiter(lex, &is);
	path = get_file(data);
	printf("**%s**\n", value);
	printf("**%s**\n", path);
	while (1337)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(1);
		if (str && str[0] != '\n')
			if (append_line(data, str, value, is))
				break ;
		free(str);
	}
	close(data->in);
	data->in = open(path, O_RDONLY, 0644);
	free(path);
	free(value);
	return (1);
}
