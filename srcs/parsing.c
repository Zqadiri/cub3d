/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:52:29 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/04 14:27:43 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int			check_elem_nbr(t_index *m)
{
	int i;
	int cpt;

	i = -1;
	cpt = 0;
	while (m->parse.data[++i] != '\0')
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
	}
	return (1);
}

int			is_empty(char *s)
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

int			parse_map(int fd, t_index *m)
{
	printf("parse_map\n");
	char	*line;
	int		end;

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

int			parse_data(int fd, t_index *m)
{
	printf("parse_data\n");
	char	*line;
	int		i;

	i = 0;
	m->parse.data = "";
	line = "";
	while (is_empty(line))
		get_next_line(fd, &line);
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\n");
	while (get_next_line(fd, &line))
	{
		while (is_empty(line))
			get_next_line(fd, &line);
		if (digit(line)){ // You should break here.
			printf("Error\n");
			return (-1);
		}
		printf("%s\n", line);
		if (!digit(line))
		{
			m->parse.data = ft_strjoin(m->parse.data, line);
			m->parse.data = ft_strjoin(m->parse.data, "\n");
			free(line);
			line = NULL;
		}
	}
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\0");
	free(line);
	line = NULL;
	return (1);
}

int			parse_cub(t_index *m, char *filename)
{
	printf("parse_cub\n");
	int		fd;

	fd = open(filename, O_RDONLY);
	if (parse_data(fd, m) < 0)
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
