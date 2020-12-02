/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:46:15 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/02 11:52:32 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		malloc_size_sprite(t_index *m)
{
	// if (!(m->spr.sprites_x = malloc(sizeof(double *) * m->spr.numsprites + 1)))
	// {
	// 	write(1, "Error\n", 6);
	// 	write(1, "Can't malloc the sprite", 23);
	// 	exit_all(m);
	// 	return (-1);
	// }
	// if (!(m->spr.sprites_y = malloc(sizeof(double *) * m->spr.numsprites + 1)))
	// {
	// 	write(1, "Error\n", 6);
	// 	write(1, "Can't malloc the sprite", 23);
	// 	exit_all(m);
	// 	return (-1);
	// }
	if (!(m->s_xy = (t_spr_xy *)malloc(sizeof(t_spr_xy) * m->spr.numsprites + 1)))
	{
		write(1, "Error\n", 6);
		write(1, "Can't malloc the sprite", 23);
		exit_all(m);
		return (-1);
	}
	
	if (!(m->spr.order = malloc(sizeof(int *) * m->spr.numsprites + 1)))
	{
		write(1, "Error\n", 6);
		write(1, "Can't malloc the sprite", 23);
		exit_all(m);
		return (-1);
	}
	// if (!(m->spr.dist = (double *)malloc(sizeof(double) * m->spr.numsprites + 1)))
	// {
	// 	write(1, "Error\n", 6);
	// 	write(1, "Can't malloc the sprite", 23);
	// 	exit_all(m);
	// 	return (-1);
	// }
	return (1);
}

void	parse_sprites(t_index *m)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (m->parse.map[(int)i] != NULL)
	{
		j = 0;
		while (m->parse.map[(int)i][(int)j] != '\0')
		{
			if (m->parse.map[(int)i][(int)j] == '2')
			{
				// m->spr.sprites_x[k] = (double)j + 0.5;
				// m->spr.sprites_y[k] = (double)i + 0.5;
				m->s_xy[k].x = (double)j + 0.5;
				m->s_xy[k].y = (double)i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
}

int		get_sprites(t_index *m)
{
	if (malloc_size_sprite(m) < 0)
		return (-1);
	parse_sprites(m);
	return (1);
}
