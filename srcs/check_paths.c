/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:31:27 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/29 16:11:02 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void		calculate_colors(t_index *m)
{
	if (m->data.side == 1 && (m->data.map_y > m->data.pos_y))
		m->text.color = (int *)m->text.s_color;
	else if (m->data.side == 1 && (m->data.map_y < m->data.pos_y))
		m->text.color = (int *)m->text.n_color;
	else if (m->data.side == 0 && (m->data.map_x > m->data.pos_x))
		m->text.color = (int *)m->text.e_color;
	else
		m->text.color = (int *)m->text.w_color;
	m->spr.color = (int *)m->spr.sprite_text;
}

/*
** wallx is where exactly the wall was hit
** find x coordinate on the texture .
** step is how much to increase the texture coordinate per screen pixel
** tex_pos : starting texture coordinate
*/

void		calculate_textures(t_index *m)
{
	float	wallx;

	if (m->data.side == 0)
		wallx = m->data.pos_y + m->data.perp_wall_dist * m->data.ray_dir_y;
	else
		wallx = m->data.pos_x + m->data.perp_wall_dist * m->data.ray_dir_x;
	wallx -= floor((wallx));
	m->text.tex_x = (int)(wallx * m->text.tex_height);
	if (m->data.side == 0 && m->data.ray_dir_x > 0)
		m->text.tex_x = m->text.tex_width - m->text.tex_x - 1;
	if (m->data.side == 1 && m->data.ray_dir_y < 0)
		m->text.tex_x = m->text.tex_width - m->text.tex_x - 1;
	m->text.step = 1.0 * m->text.tex_height / m->data.line_height;
	m->text.tex_pos = (m->data.draw_start - m->el.res_y / 2
					+ m->data.line_height / 2) * m->text.step;
}

void		verline(int i, t_index *m)
{
	int j;
	int k;
	int y;

	j = 0;
	y = m->data.draw_start;
	while (j < y)
	{
		m->img.addr[j * m->el.res_x + i] = m->el.c_color_hex;
		j++;
	}
	while (y < m->data.draw_end)
	{
		m->text.tex_y = (int)m->text.tex_pos & (m->text.tex_height - 1);
		m->text.tex_pos += m->text.step;
		m->img.addr[y * m->el.res_x + i] =
			m->text.color[m->text.tex_y * m->text.tex_height + m->text.tex_x];
		y++;
	}
	k = y;
	while (k < (int)m->el.res_y)
	{
		m->img.addr[k * m->el.res_x + i] = m->el.f_color_hex;
		k++;
	}
}
