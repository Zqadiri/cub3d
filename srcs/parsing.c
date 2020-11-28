/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:52:29 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/28 14:04:50 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int		check_elem_nbr(t_index *m)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (m->parse.data[i] != '\0')
	{
		if (m->parse.data[i] == 'R')
			cpt++;
		if (m->parse.data[i] == 'N' && m->parse.data[i + 1] == 'O')
			cpt++;
		if (m->parse.data[i] == 'S')
		{
			if (m->parse.data[i + 1] == 'O')
				cpt++;
			else
				cpt++;
		}
		if (m->parse.data[i] == 'W' && m->parse.data[i + 1] == 'E')
			cpt++;
		if (m->parse.data[i] == 'E' && m->parse.data[i + 1] == 'A')
			cpt++;
		if (m->parse.data[i] == 'F')
			cpt++;
		if (m->parse.data[i] == 'C')
			cpt++;
		i++;
	}
	if (cpt != 8)
		write_el_error();
	return (1);
}

/*
**jump to next map square, OR in x-direction,
**OR in y-direction & Check if ray has hit a wall
*/

int		is_empty(char *s)
{
	int i;

	i = 0;
	if (s[0] == '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		parse_map(int fd, t_index *m)
{
	char *line;
	int end;

	end = 0;
	line = "";
	m->parse.map_string = "";
	while (is_empty(line))
		get_next_line(fd, &line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
	while (get_next_line(fd, &line))
	{
		if (!is_empty(line) && end)
			write_error_one(m);
		if (is_empty(line))
		{
			end = 1;
			continue;
		}
		m->parse.map_string = ft_strjoin(m->parse.map_string, line);
		m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
		free(line);
		line = NULL;
	}
	m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, "\0");
	printf("%s\n", m->parse.map_string);
	free(line);
	line = NULL;
	return (1);
}

int		parse_data(int fd, t_index *m)
{
	char	*line;
	int		i;

	i = 0;
	m->parse.data = "";
	line = "";
	while (is_empty(line))
		get_next_line(fd, &line);
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\n");
	while (get_next_line(fd, &line) && i < 7)
	{
		while (line[0] == '\0')
			get_next_line(fd, &line);
		if (!digit(line))
		{
			m->parse.data = ft_strjoin(m->parse.data, line);
			m->parse.data = ft_strjoin(m->parse.data, "\n");
			free(line);
			line = NULL;
			i++;
		}
	}
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\0");
	free(line);
	line = NULL;
	return (1);
}

int		parse_cub(t_index *m, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (parse_data(fd, m) < 0)
		return (-1);
	if (check_elem_nbr(m) < 0)
		return (-1);
	if (parse_map(fd, m) < 0)
		return (-1);
	close(fd);
	if (create_map(m) < 0)
		return (-1);
	if (create_good_size_map(m) < 0)
		return (-1);
	if (get_sprites(m) < 0)
		return (-1);
	if (get_elements(m) < 0)
		return (-1);
	if (check_elements_errors(m) < 0)
		return (-1);
	if (check_map_errors(m) < 0)
		return (-1);
	return (1);
}
