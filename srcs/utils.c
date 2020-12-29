/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:08:16 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/29 16:15:54 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		exit_all(t_index *m)
{
	free_map(m);
	free_elem(m);
	free_text(m);
	free_win(m);
	exit(0);
	return (-1);
}

int		digit(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0' && !ft_isalpha(c[i]))
	{
		if (c[i] >= '0' && c[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

int		transform_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	create_hex_color(t_index *m)
{
	m->el.c_color_hex = transform_to_hex(m->el.c_r,
		m->el.c_g, m->el.c_b);
	m->el.f_color_hex = transform_to_hex(m->el.f_r,
		m->el.f_g, m->el.f_b);
}

int		check_file_cub(char *filename)
{
	int	i;

	i = ft_strlen(filename) - 1;
	if (filename[i] != 'b' || filename[i - 1] != 'u' ||
		filename[i - 2] != 'c' || filename[i - 3] != '.')
	{
		write(1, "Error\n", 6);
		write(1, "wrong file name\n", 16);
		exit(0);
	}
	return (1);
}
