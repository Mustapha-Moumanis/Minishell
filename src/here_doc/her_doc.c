/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumani <mmoumani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:47:06 by mmoumani          #+#    #+#             */
/*   Updated: 2023/06/03 16:07:56 by mmoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "get_next_line/get_next_line.h"

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
	data->in = open(path, O_CREAT | O_APPEND | O_RDWR, 0644);
	return (path);
}

int	append_line(t_data *data, char *str, char *value, int is)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strtrim(str, "\n");
	if (!ft_strcmp(tmp, value))
		return (free(str), free(tmp), 1);
	if (is == 0 && ft_strchr(tmp, '$'))
	{
		tmp2 = update_line(data, tmp);
		ft_putstr_fd(tmp2, data->in);
		free(tmp2);
	}
	else
		ft_putstr_fd(str, data->in);
	return (free(tmp), 0);
}

void	child_event(t_data *data, char *value, int is)
{
	char	*str;

	signal(SIGINT, exc_child_sig);
	signal(SIGQUIT, SIG_IGN);
	while (1337)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(1);
		if (!str)
			exit (1);
		else
			if (append_line(data, str, value, is))
				break ;
		free(str);
	}
	exit (1);
}

int	her_doc(t_data *data, t_elem **lex, int var)
{
	char	*value;
	char	*path;
	int		fd;
	int		is;

	is = 0;
	fd = data->in;
	value = get_delimiter(lex, NULL, NULL, &is);
	path = get_file(data);
	var = fork();
	if (var == -1)
		return (ft_error("fork fail\n"));
	if (var == 0)
		child_event(data, value, is);
	wait(&var);
	if (WEXITSTATUS(var) == 1)
	{
		close(data->in);
		data->in = fd;
		if (fd != -1)
			data->in = open(path, O_RDONLY, 0644);
	}
	else
		data->error = 2;
	return (free(value), free(path), 1);
}
