/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:16:57 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/30 11:17:48 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    vertical(t_index *m)
{
    m->spr.stripe = m->spr.draw_start_x;
    while (m->spr.stripe < m->spr.draw_end_x)
    {
        m->spr.tex_x = (int)((m->spr.stripe - (-m->spr.spr_width / 2 +
                        m->spr.spr_screen_x)) * 64 / m->spr.spr_width);
        if (m->spr.transform_y > 0 && m->spr.stripe > 0
                && m->spr.stripe < m->el.res_x
                && m->spr.transform_y < m->spr.spr_buffer[m->spr.stripe]
                && m->spr.tex_x < 64)
        {
            draw_sprite(m);
        }
        m->spr.stripe++; 
    }
}

void    draw_sprite(t_index *m)
{
    int y;
    int d;

    d = 0;
    y = m->spr.draw_start_y;
    while (y < m->spr.draw_end_y)
    {
        d = (y - m->spr.v_move_screen) * 256 - m->el.res_y * 128 +
                m->spr.spr_height * 128;
        m->spr.tex_y = ((d * 64) / m->spr.spr_height) / 256;
        if ((m->spr.color[64 * m->spr.tex_y + m->spr.tex_x] & 0x00FFFFFF) != 0)
            m->img.addr[y * m->el.res_x + m->spr.stripe] =
            m->spr.color[64 * m->spr.tex_y + m->spr.tex_x];
        y++;
    }
}
