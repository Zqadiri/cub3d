/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:08:16 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/10 11:39:40 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"


int		exit_it(t_index *m)
{
	free_win(m);
	//free_map(m);
	free_elem(m);
	exit(0);
	return (-1);
}

int		exit_all(t_index *m)
{
	free_win(m);
	free_map(m);
	free_elem(m);
	exit(0);
	return (-1);
}

int		transform_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	create_hex_color(t_index *m)
{
	m->el.c_color_hex = transform_to_hex(m->el.c_red,
		m->el.c_green, m->el.c_blue);
	m->el.f_color_hex = transform_to_hex(m->el.f_red,
		m->el.f_green, m->el.f_blue);
}

int		new_strlen(char *s)
{                                                                                                                                   
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int		calcul_digit(t_index *m, int i)
{
	int	digit;

	digit = 0;
	while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
	while (m->el.elem[m->el.resolution_line][i] >= '0' &&
		m->el.elem[m->el.resolution_line][i] <= '9')
	{
		digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
		i++;
	}
	m->el.res_x = digit;
	return (i);
}


