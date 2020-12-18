/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:10:27 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/18 20:29:04 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** find the x-coordinate in camera space
** calculate ray direction of a ray that has been cast
** distance the ray has to travel to go from 1 x-side to the next x-side
** and from 1 y-side to the next y-side
*/

void		calculate_ray_pos_dir(int i, t_index *m)
{
	m->data.camera_x = 2 * i / (float)m->el.res_x - 1;
	m->data.ray_dir_x = m->data.dir_x + m->data.plane_x * m->data.camera_x;
	m->data.ray_dir_y = m->data.dir_y + m->data.plane_y * m->data.camera_x;
	m->data.map_x = (int)m->data.pos_x;
	m->data.map_y = (int)m->data.pos_y;
	m->data.delta_dist_x = sqrt(1 + (m->data.ray_dir_y * m->data.ray_dir_y)
							/ (m->data.ray_dir_x * m->data.ray_dir_x));
	m->data.delta_dist_y = sqrt(1 + (m->data.ray_dir_x * m->data.ray_dir_x)
							/ (m->data.ray_dir_y * m->data.ray_dir_y));
}

/*
** If the ray direction has a negative x-component, stepX is -1,
** if the ray direciton has a positive x-component it's +1.
** If the x-component is 0, it doesn't matter what value stepX has since
** it'll then be unused. The same goes for the y-component.
*/

void		calculate_step_sidedist(t_index *m)
{
	if (m->data.ray_dir_x < 0)
	{
		m->data.step_x = -1;
		m->data.side_dist_x = (m->data.pos_x - m->data.map_x) *
						m->data.delta_dist_x;
	}
	else
	{
		m->data.step_x = 1;
		m->data.side_dist_x = m->data.delta_dist_x *
						(m->data.map_x + 1.0 - m->data.pos_x);
	}
	if (m->data.ray_dir_y < 0)
	{
		m->data.step_y = -1;
		m->data.side_dist_y = (m->data.pos_y - m->data.map_y) *
						m->data.delta_dist_y;
	}
	else
	{
		m->data.step_y = 1;
		m->data.side_dist_y = (m->data.map_y + 1.0 - m->data.pos_y) *
						m->data.delta_dist_y;
	}
}

/*
** sideDistX and sideDistY get incremented with deltaDistX with
** every jump in their direction,
** and mapX and mapY get incremented with stepX and stepY
*/

void		perform_dda(t_index *m, int hit)
{
	while (hit == 0)
	{
		if (m->data.side_dist_x < m->data.side_dist_y)
		{
			m->data.side_dist_x += m->data.delta_dist_x;
			m->data.map_x += m->data.step_x;
			m->data.side = 0;
		}
		else
		{
			m->data.side_dist_y += m->data.delta_dist_y;
			m->data.map_y += m->data.step_y;
			m->data.side = 1;
		}
		if (m->parse.map[m->data.map_y][m->data.map_x] == '1')
			hit = 1;
	}
}

/*
** Calculate distance projected on camera direction
** mapX-posX+(1-stepX)/2) is the number of squares
** the ray has crossed in X direction
*/

void		calculate_dist(t_index *m)
{
	if (m->data.side == 0)
		m->data.perp_wall_dist = (m->data.map_x - m->data.pos_x +
								(1 - m->data.step_x) / 2) / m->data.ray_dir_x;
	else
		m->data.perp_wall_dist = (m->data.map_y - m->data.pos_y +
								(1 - m->data.step_y) / 2) / m->data.ray_dir_y;
}

/*
** Calculate height of line to draw on screen
*/

void		calculate_wall_height(t_index *m)
{
	m->data.wall_height = m->el.res_y;
	m->data.line_height = (int)(m->data.wall_height / m->data.perp_wall_dist);
	m->data.draw_start = -m->data.line_height / 2 + m->el.res_y / 2;
	if (m->data.draw_start < 0)
		m->data.draw_start = 0;
	m->data.draw_end = m->data.line_height / 2 + m->el.res_y / 2;
	if (m->data.draw_end >= m->el.res_y)
		m->data.draw_end = m->el.res_y - 1;
}
