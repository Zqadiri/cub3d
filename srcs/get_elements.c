/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:55:23 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/16 12:14:41 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	int					i;
	unsigned long int	digit;

	digit = 0;
	i = 1;
	i = calcul_digit(m, i);
	while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
	if (m->el.elem[m->el.resolution_line][i] == '\0' ||
			!ft_isdigit(m->el.elem[m->el.resolution_line][i]))
		write_el_error(m, 1);
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
			write_el_error(m, 1);
		i++;
	}
	return (1);
}

void		get_floor_color(t_index *m)
{
	int i;

	i = 0;
	while (m->el.elem[m->el.f_l][++i] == ' ')
		i++;
	while (m->el.elem[m->el.f_l][i] >= '0' && m->el.elem[m->el.f_l][i] <= '9')
		m->el.f_r = (m->el.f_r * 10) + m->el.elem[m->el.f_l][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.f_l][++i] != ',')
		write_error_floor(m);
	while (!ft_isdigit(m->el.elem[m->el.f_l][++i]))
		write_error_floor(m);
	while (m->el.elem[m->el.f_l][i] >= '0' && m->el.elem[m->el.f_l][i] <= '9')
		m->el.f_g = (m->el.f_g * 10) + m->el.elem[m->el.f_l][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.f_l][++i] != ',')
		write_error_floor(m);
	while (!ft_isdigit(m->el.elem[m->el.f_l][++i]))
		write_error_floor(m);
	while (m->el.elem[m->el.f_l][i] >= '0' && m->el.elem[m->el.f_l][i] <= '9')
		m->el.f_b = (m->el.f_b * 10) + m->el.elem[m->el.f_l][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.f_l][++i] != '\0')
		write_error_end_floor(m, i);
}

void		get_ceilling_color(t_index *m)
{
	int i;

	i = 0;
	while (m->el.elem[m->el.c_l][++i] == ' ')
		i++;
	while (m->el.elem[m->el.c_l][i] >= '0' && m->el.elem[m->el.c_l][i] <= '9')
		m->el.c_r = (m->el.c_r * 10) + m->el.elem[m->el.c_l][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.c_l][++i] != ',')
		write_error_ceilling(m);
	while (!ft_isdigit(m->el.elem[m->el.c_l][++i]))
		write_error_ceilling(m);
	while (m->el.elem[m->el.c_l][i] >= '0' && m->el.elem[m->el.c_l][i] <= '9')
		m->el.c_g = (m->el.c_g * 10) + m->el.elem[m->el.c_l][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.c_l][++i] != ',')
		write_error_ceilling(m);
	while (!ft_isdigit(m->el.elem[m->el.c_l][++i]))
		write_error_ceilling(m);
	while (m->el.elem[m->el.c_l][i] >= '0' && m->el.elem[m->el.c_l][i] <= '9')
		m->el.c_b = (m->el.c_b * 10) + m->el.elem[m->el.c_l][i++] - '0';
	i = i - 1;
	while (m->el.elem[m->el.c_l][++i] != '\0')
		write_error_end_ceilling(m, i);
}

int		get_elements(t_index *m)
{
	m->el.elem = ft_split(m->parse.data, '\n');
	if (create_elements_lines(m) < 0)
		return (-1);
	get_floor_color(m);
	get_ceilling_color(m);
	if (check_valid_color(m) < 0)
		return (-1);
	if (get_resolution(m) < 0)
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
