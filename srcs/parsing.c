/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:52:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/16 12:29:13 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int			parse_map(int fd, t_index *m)
{
	char *pfree;
	int	not_empty;
	int	last;

	last = 0; 
	not_empty = 0;
	m->parse.map_str = ft_strdup("");
	while (m->parse.ret)
	{
		m->parse.ret = get_next_line(fd, &m->parse.line);
		if (last == 1)
			error_data(m, 3);
		if (!digit(m->parse.line) && digit(m->parse.map_str))
			last = 1;
		else
		{
			pfree = m->parse.map_str;
			m->parse.map_str = ft_strjoin(m->parse.map_str, m->parse.line);
			free(pfree);
			pfree = m->parse.map_str;
			m->parse.map_str = ft_strjoin(m->parse.map_str, "\n");
			free(pfree);	
		}
		free(m->parse.line);	
	}
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
		write_el_error(m, 2);
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
	(digit(line)) ? error_data(m, 2) : 1;
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
	(m->parse.i < 7) ? error_data(m, 1) : 1;
	clear(save, line);
	return (1);
}

int			parse_cub(t_index *m, char *filename)
{
	int		fd;
	char	*pfree;

	pfree = NULL;
	fd = open(filename, O_RDONLY);
	if (parse_data(fd, m) < 0)
		return (-1);
	if (parse_map(fd, m) < 0)
		return (-1);
	(!digit(m->parse.map_str)) ? error_data(m, 1) : 1;
	if (check_map_characters(m) < 0)
		return (-1);
	if (check_elem_nbr(m) < 0)
		return (-1);
	close(fd);
	if (create_map(m) < 0)
		return (-1);
	if (get_sprites(m) < 0)
		return (-1);
	if (get_elements(m) < 0)
		return (-1);
	if (check_elements_errors(m) < 0)
		return (-1);
	return (1);
}
