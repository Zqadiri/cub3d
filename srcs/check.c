/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:43:29 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/01 18:16:18 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_position2(t_index *m, int i, int j)
{
	if ((ft_isalpha(m->parse.map[i][j])))
	{
		m->parse.x_pos_init = (double)j + 0.5;
		m->parse.y_pos_init = (double)i + 0.5;
		if (m->parse.dir == 0)
			m->parse.dir = m->parse.map[i][j];
		else
			return (return_error(m));
		m->parse.map[i][j] = '0';
	}
	if (m->parse.map[i][j] == '2')
		m->spr.numsprites += 1;
	return (1);
}

int		get_position(t_index *m)
{
	int i;
	int j;

	i = 0;
	while (m->parse.map[i] != NULL)
	{
		j = 0;
		while (m->parse.map[i][j] != '\0')
		{
			get_position2(m, i, j);
			j++;
		}
		i++;
	}
	m->parse.line_nbr = i;
	m->parse.column_nbr = j;
	return (1);
}

int		check_borders_columns(t_index *m)
{
	int	i;
	int	j;

	i = 0;
	while (m->parse.map[i] != NULL)
	{
		j = 0;
		while (m->parse.map[i][j] != '\0')
			j++;
		if (m->parse.map[i][j - 1] != '1' && m->parse.map[i][j - 1] != ' ')
			return_error_exit(m);
		i++;
	}
	i = 0;
	while (m->parse.map[i] != NULL)
	{
		if (m->parse.map[i][0] != '1' && m->parse.map[i][0] != ' ')
			return_error_exit(m);
		i++;
	}
	return (1);
}

int		check_borders_lines(t_index *m)
{
	int j;

	j = 0;
	while (m->parse.map[0][j] != '\0')
	{
		if (m->parse.map[0][j] != '1' && m->parse.map[0][j] != ' ')
			return_error_exit(m);
		j++;
	}
	j = 0;
	while (m->parse.map[m->parse.line_nbr - 1][j] != '\0')
	{
		if ((m->parse.map[m->parse.line_nbr - 1][j] != '1') &&
			(m->parse.map[m->parse.line_nbr - 1][j] != ' '))
			return_error_exit(m);
		j++;
	}
	return (1);
}

int		check_letters(t_index *m, int i, int j)
{
	if (m->el.elem[i][j] == 'R')
		m->el.resolution_line = i;
	if (m->el.elem[i][j] == 'N')
		m->el.north_line = i;
	if (m->el.elem[i][j] == 'S')
	{
		if (m->el.elem[i][j + 1] == 'O')
			m->el.south_line = i;
		else
			m->el.sprite_line = i;
	}
	if (m->el.elem[i][j] == 'W')
		m->el.west_line = i;
	if (m->el.elem[i][j] == 'E')
		m->el.east_line = i;
	if (m->el.elem[i][j] == 'F')
		m->el.f_l = i;
	if (m->el.elem[i][j] == 'C')
		m->el.c_l = i;
	return (1);
}
