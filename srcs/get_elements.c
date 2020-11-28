/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:55:23 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/28 14:37:27 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int		create_elements_lines(t_index *m)
{
	int i;
	int j;

	i = 0;
	while (m->el.elem[i] != NULL)
	{
		j = 0;
		while (m->el.elem[i][j] != '\0')
		{
			if (check_letters(m, i, j) < 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		get_resolution(t_index *m)
{
	int	i;
	int	digit;

	digit = 0;
	i = 1;
	i = calcul_digit(m, i);
	while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
	if (m->el.elem[m->el.resolution_line][i] == '\0' ||
			!ft_isdigit(m->el.elem[m->el.resolution_line][i]))
		write_error_res();
	while (m->el.elem[m->el.resolution_line][i] >= '0' &&
			m->el.elem[m->el.resolution_line][i] <= '9')
	{
		digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
		i++;
	}
	m->el.res_y = digit;
	while (m->el.elem[m->el.resolution_line][i] != '\0')
	{
		if (m->el.elem[m->el.resolution_line][i] != ' ')
			write_error_res();
		i++;
	}
	return (1);
}

int		get_floor_color(t_index *m)
{
	int i;

	i = 0;
	while (m->el.elem[m->el.f_line][++i] == ' ')
		i++;
	while (m->el.elem[m->el.f_line][i] >= '0' && m->el.elem[m->el.f_line][i] <= '9')
		m->el.f_red = (m->el.f_red * 10) + m->el.elem[m->el.f_line][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.f_line][++i] != ',')
		write_error_floor(m, i);
	while (!ft_isdigit(m->el.elem[m->el.f_line][++i]))
		write_error_floor(m, i);
	while (m->el.elem[m->el.f_line][i] >= '0' && m->el.elem[m->el.f_line][i] <= '9')
		m->el.f_green = (m->el.f_green * 10) + m->el.elem[m->el.f_line][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.f_line][++i] != ',')
		write_error_floor(m, i);
	while (!ft_isdigit(m->el.elem[m->el.f_line][++i]))
		write_error_floor(m, i);
	while (m->el.elem[m->el.f_line][i] >= '0' && m->el.elem[m->el.f_line][i] <= '9')
		m->el.f_blue = (m->el.f_blue * 10) + m->el.elem[m->el.f_line][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.f_line][++i] != '\0')
		write_error_end_floor(m, i);
	return (0);
}

int		get_ceilling_color(t_index *m)
{
	int i;

	i = 0;
	while (m->el.elem[m->el.c_line][++i] == ' ')
		i++;
	while (m->el.elem[m->el.c_line][i] >= '0' && m->el.elem[m->el.c_line][i] <= '9')
		m->el.c_red = (m->el.c_red * 10) + m->el.elem[m->el.c_line][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.c_line][++i] != ',')
		write_error_ceilling(m, i);
	while (!ft_isdigit(m->el.elem[m->el.c_line][++i]))
		write_error_ceilling(m, i);
	while (m->el.elem[m->el.c_line][i] >= '0' && m->el.elem[m->el.c_line][i] <= '9')
		m->el.c_green = (m->el.c_green * 10) + m->el.elem[m->el.c_line][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.c_line][++i] != ',')
		write_error_ceilling(m, i);
	while (!ft_isdigit(m->el.elem[m->el.c_line][++i]))
		write_error_ceilling(m, i);
	while (m->el.elem[m->el.c_line][i] >= '0' && m->el.elem[m->el.c_line][i] <= '9')
		m->el.c_blue = (m->el.c_blue * 10) + m->el.elem[m->el.c_line][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.c_line][++i] != '\0')
		write_error_end_ceilling(m, i);
	return (0);
}

int		get_elements(t_index *m)
{
	//printf("1.parse data :%s\n", m->parse.data);
	m->el.elem = ft_split(m->parse.data, '\n');
	if (create_elements_lines(m) < 0)
		return (-1);
	if (get_resolution(m) < 0)
		return (-1);
	if (get_floor_color(m) < 0)
		return (-1);
	if (get_ceilling_color(m) < 0)
		return (-1);
	create_hex_color(m);
	if (!get_sprite_texture(m))
		return (-1);
	if (!get_north_texture(m))
		return (-1);
	if (!get_south_texture(m))
		return (-1);
	if (!get_west_texture(m))
		return (-1);
	if (!get_east_texture(m))
		return (-1);
	return (1);
}