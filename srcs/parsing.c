/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:52:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/10 19:03:57 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int			join_line(t_index *m, char *line, char *pfree, int last)
{
	pfree = m->parse.map_string;
	m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	free(pfree);
	pfree = m->parse.map_string;
	if (last == 1)
		m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
	else if (last == 0)
		m->parse.map_string = ft_strjoin(m->parse.map_string, "\0");
	clear(pfree, line);
	return (1);
}

int			parse_map(int fd, t_index *m)
{
	char *pfree;
	int	not_empty;
	int	last;

	last = 0; 
	not_empty = 0;
	m->parse.map_string = ft_strdup("");
	while (m->parse.ret)
	{
		m->parse.ret = get_next_line(fd, &m->parse.line);
		if (last && is_empty(m->parse.line))
			error_data(m);
		if ((not_empty && m->parse.line[0] != '\n'))
			error_data(m);
		if (check_line(m->parse.line) < 0)
			not_empty = 1;
		if (is_empty(m->parse.line) && digit(m->parse.map_string))
			last = 1;
		else
		{
			pfree = m->parse.map_string;
			m->parse.map_string = ft_strjoin(m->parse.map_string, m->parse.line);
			free(pfree);
			pfree = m->parse.map_string;
			m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
			free(pfree);	
		}
		free(m->parse.line);
	}
	printf("%s\n", m->parse.map_string);
	return (1);
}

int			parse_data_helper(t_index *m, int fd, char *line)
{
	char	*save;

	while (is_empty(line))
	{
		free(line);
		get_next_line(fd, &line);
	}
	if (digit(line))
		write_el_error(m);
	if (!digit(line))
	{
		save = m->parse.data;
		m->parse.data = ft_strjoin(m->parse.data, line);
		free(save);
		save = m->parse.data;
		m->parse.data = ft_strjoin(m->parse.data, "\n");
		clear(save, line);
		m->parse.i++;
	}
	return (1);
}

int			parse_data(int fd, t_index *m)
{
	char	*line;
	char	*save;

	m->parse.data = "";
	line = NULL;
	while (is_empty(line))
	{
		free(line);
		get_next_line(fd, &line);
	}
	(digit(line)) ? error_data(m) : 1;
	m->parse.data = ft_strjoin(m->parse.data, line);
	save = m->parse.data;
	m->parse.data = ft_strjoin(m->parse.data, "\n");
	clear(save, line);
	while (get_next_line(fd, &line) && m->parse.i < 7)
		parse_data_helper(m, fd, line);
	save = m->parse.data;
	m->parse.data = ft_strjoin(m->parse.data, line);
	free(save);
	save = m->parse.data;
	m->parse.data = ft_strjoin(m->parse.data, "\0");
	(m->parse.i < 7) ? error_data(m) : 1;
	clear(save, line);
	return (1);
}

int			parse_cub(t_index *m, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (parse_data(fd, m) < 0)
		return (-1);
	if (parse_map(fd, m) < 0)
		return (-1);
	(!digit(m->parse.map_string)) ? error_data(m) : 1;
	if (check_elem_nbr(m) < 0)
		return (-1);
	close(fd);
	if (create_map(m) < 0)
		return (-1);
	if (create_good_size_map(m) < 0)
		return (-1);
	if (check_map_errors(m) < 0)
		return (-1);
	if (get_sprites(m) < 0)
		return (-1);
	if (get_elements(m) < 0)
		return (-1);
	if (check_elements_errors(m) < 0)
		return (-1);
	return (1);
}
