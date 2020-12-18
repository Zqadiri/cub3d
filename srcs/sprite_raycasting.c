/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:54:32 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/18 20:28:59 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** calculate height of the sprite on screen
** calculate lowest and highest pixel to fill in current stripe
*/

void		calculate_start_end(t_index *m)
{
	m->spr.spr_height = abs((int)(m->el.res_y / m->spr.transform_y));
	m->spr.draw_start_y = -m->spr.spr_height / 2 + m->el.res_y / 2;
	if (m->spr.draw_start_y < 0)
		m->spr.draw_start_y = 0;
	m->spr.draw_end_y = m->spr.spr_height / 2 + m->el.res_y / 2;
	if (m->spr.draw_end_y >= m->el.res_y)
		m->spr.draw_end_y = m->el.res_y;
	m->spr.spr_width = abs((int)(m->el.res_y / m->spr.transform_y));
	m->spr.draw_start_x = -m->spr.spr_width / 2 + m->spr.spr_screen_x;
	if (m->spr.draw_start_x < 0)
		m->spr.draw_start_x = 0;
	m->spr.draw_end_x = m->spr.spr_width / 2 + m->spr.spr_screen_x;
	if (m->spr.draw_end_x >= m->el.res_x)
		m->spr.draw_end_x = m->el.res_x;
}

void		order(t_index *m)
{
	int i;

	i = -1;
	while (++i < m->spr.numsprites)
	{
		m->s_xy[i].dist = ((m->data.pos_x - m->s_xy[i].x) *
				(m->data.pos_x - m->s_xy[i].x) + (m->data.pos_y -
					m->s_xy[i].y) * (m->data.pos_y - m->s_xy[i].y));
	}
}

/*
** sort sprites from far to close
*/

void		sort_sprites(t_index *m)
{
	int		i;
	int		j;
	double	tmp;

	order(m);
	i = -1;
	while (++i < m->spr.numsprites)
	{
		j = -1;
		while (++j < m->spr.numsprites - 1)
		{
			if (m->s_xy[j].dist < m->s_xy[j + 1].dist)
			{
				tmp = m->s_xy[j].dist;
				m->s_xy[j].dist = m->s_xy[j + 1].dist;
				m->s_xy[j + 1].dist = tmp;
				tmp = m->s_xy[j].x;
				m->s_xy[j].x = m->s_xy[j + 1].x;
				m->s_xy[j + 1].x = tmp;
				tmp = m->s_xy[j].y;
				m->s_xy[j].y = m->s_xy[j + 1].y;
				m->s_xy[j + 1].y = tmp;
			}
		}
	}
}

/*
** transform sprite with the inverse camera matrix
**[ planeX   dirX ] -1                                   [ dirY      -dirX ]
**[               ]     =  1/(planeX*dirY-dirX*planeY) * [                 ]
**[ planeY   dirY ]                                      [ -planeY  planeX ]
*/

void		update(t_index *m, int i)
{
	m->spr.spr_x = m->s_xy[i].x - m->data.pos_x;
	m->spr.spr_y = m->s_xy[i].y - m->data.pos_y;
	m->spr.invdet = 1.0 / (m->data.plane_x * m->data.dir_y -
			m->data.dir_x * m->data.plane_y);
	m->spr.transform_x = m->spr.invdet * (m->data.dir_y * m->spr.spr_x -
			m->data.dir_x * m->spr.spr_y);
	m->spr.transform_y = m->spr.invdet * (-m->data.plane_y * m->spr.spr_x +
			m->data.plane_x * m->spr.spr_y);
	m->spr.spr_screen_x = (int)((m->el.res_x / 2) *
			(1 + m->spr.transform_x / m->spr.transform_y));
}

/*
** loop through every vertical stripe of the sprite on screen
** the conditions in the if are:
** 1) it's in front of camera plane so you don't see things behind you
** 2) it's on the screen (left)
** 3) it's on the screen (right)
** 4) ZBuffer, with perpendicular distance
*/

void		sprite_raycasting(t_index *m)
{
	int	i;

	sort_sprites(m);
	i = -1;
	while (++i < m->spr.numsprites)
	{
		update(m, i);
		calculate_start_end(m);
		m->spr.stripe = m->spr.draw_start_x;
		while (m->spr.stripe < m->spr.draw_end_x)
		{
			m->spr.tex_x = (int)(256 * (m->spr.stripe -
						(-m->spr.spr_width / 2 + m->spr.spr_screen_x)) *
						64 / m->spr.spr_width) / 256;
			if (m->spr.transform_y > 0 && m->spr.stripe >= 0
					&& m->spr.stripe < m->el.res_x
					&& m->spr.transform_y < m->spr.spr_buffer[m->spr.stripe]
					&& m->spr.tex_x < 64)
			{
				draw_sprite(m);
			}
			m->spr.stripe++;
		}
	}
}
