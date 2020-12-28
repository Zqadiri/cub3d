/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:58:47 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/28 15:46:54 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_paths(t_index *m)
{
	if (m->el.north_path)
	{
		free(m->el.north_path);
		m->el.north_path = 0;
	}
	if (m->el.south_path)
	{
		free(m->el.south_path);
		m->el.south_path = 0;
	}
	if (m->el.east_path)
	{
		free(m->el.east_path);
		m->el.east_path = 0;
	}
	if (m->el.west_path)
	{
		free(m->el.west_path);
		m->el.west_path = 0;
	}
}

void	free_elem(t_index *m)
{
	int i;

	i = -1;
	if (m->el.elem)
	{
		while (++i < 8)
		{
			free(m->el.elem[i]);
			m->el.elem[i] = 0;
		}
		free(m->el.elem);
		m->el.elem = 0;
	}
	free_paths(m);
	if (m->el.spr_path)
	{
		free(m->el.spr_path);
		m->el.spr_path = 0;
	}
}

void	free_map(t_index *m)
{
	int i;

	i = -1;
	if (m->parse.map)
	{
		while (++i < m->parse.line_nbr)
		{
			free(m->parse.map[i]);
			m->parse.map[i] = 0;
		}
		free(m->parse.map);
		m->parse.map = 0;
	}
	if (m->parse.map_string)
	{
		free(m->parse.map_string);
		m->parse.map_string = 0;
	}
}

void	free_win(t_index *m)
{
	if (m->img.img)
		mlx_destroy_image(m->win.mlx_ptr, m->img.img);
	if (m->win.mlx_win)
		mlx_destroy_window(m->win.mlx_ptr, m->win.mlx_win);
}

void	free_text(t_index *m)
{
	if (m->spr.spr_buffer)
	{
		free(m->spr.spr_buffer);
		m->spr.spr_buffer = 0;
	}
	if (m->parse.data)
	{
		free(m->parse.data);
		m->parse.data = 0;
	}
	if (m->s_xy)
	{
		free(m->s_xy);
		m->s_xy = 0;
	}
}
