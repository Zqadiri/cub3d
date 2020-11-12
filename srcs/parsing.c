/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:52:29 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/11 17:13:13 by zqadiri          ###   ########.fr       */
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
			if (m->parse.data[i] == 'N'&& m->parse.data[i + 1] == 'O')
				cpt++;
			if (m->parse.data[i] == 'S' )
			{
				if (m->parse.data[i + 1] == 'O')
					cpt++;
				else
					cpt++;
			}	
			if (m->parse.data[i] == 'W' && m->parse.data[i + 1] == 'E')
				cpt++;
			if (m->parse.data[i] == 'E'  && m->parse.data[i + 1] == 'A')
				cpt++;
			if (m->parse.data[i] == 'F')
				cpt++;
			if (m->parse.data[i] == 'C')
				cpt++;
			i++;
		}	
	//printf("cpt %d\n", cpt);
	if (cpt != 8)
		write_el_error();
	return (1);
}

int		parse_map(int fd, t_index *m)
{
	printf("in 5\n");
	char *line;

	line = "";
	m->parse.map_string = "";
	while (line[0] == '\0')
		get_next_line(fd, &line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
	while (get_next_line(fd, &line))
	{
		if (line[0] == '\0')
			write_error_one(m);
		m->parse.map_string = ft_strjoin(m->parse.map_string, line);
		m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
		free(line);
		line = NULL;
	}
	m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, "\0");
	free(line);
	line = NULL;
	printf("-%s-\n", m->parse.map_string);
	printf("out 5\n");
	return (1);
}

int		parse_data(int fd, t_index *m)
{
	printf("in 4\n");
	char	*line;
	int		i;
	int 	r;
 
	i = 0;
	m->parse.data = "";
	while (get_next_line(fd, &line) != 0 && line[0] == '\0' )
		get_next_line(fd, &line);
	//printf("R LINE  :%s\n", line);
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\n");
	while (/*(r =*/ get_next_line(fd, &line) && i < 7)
	{
		while ( line[0] == '\0')
			/*r =*/ get_next_line(fd, &line);
		//printf("r = %d\n", r);
		if (!ft_isdigit(line[0]) /*&& r != 0*/)
		{
			m->parse.data = ft_strjoin(m->parse.data, line);
			m->parse.data = ft_strjoin(m->parse.data, "\n");
			free(line);
			line = NULL;
			i++;
		}
		/*else
			error_map(m);	*/	
	}
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\0");
	free(line);
	line = NULL;
	//printf("parse data :%s\n", m->parse.data);
	//if (r == 0)
		//exit_it(m);
	printf("out 4\n");
	return (1);
}

int		parse_cub(t_index *m, char *filename)
{
	//printf("in 1\n");
	int	fd;

	fd = open(filename, O_RDONLY);
	if (parse_data(fd, m) < 0)
		return (-1);
	if (check_elem_nbr(m) < 0)
		return(-1);
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

