/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:16:57 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/30 09:45:31 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** for every pixel of the current stripe
** get current color from the texture
** paint pixel if it isn't black, black is the invisible color
*/

void	draw_sprite(t_index *m)
{
	int	y;
	int	d;

	d = 0;
	y = m->spr.draw_start_y;
	while (y < m->spr.draw_end_y)
	{
		d = (y) * 256 - m->el.res_y * 128 +
			m->spr.spr_height * 128;
		m->spr.tex_y = ((d * 64) / m->spr.spr_height) / 256;
		if ((m->spr.color[64 * m->spr.tex_y + m->spr.tex_x] & 0x00FFFFFF) != 0)
		{
			m->img.addr[y * m->el.res_x + m->spr.stripe] =
				m->spr.color[64 * m->spr.tex_y + m->spr.tex_x];
		}
		y++;
	}
}
