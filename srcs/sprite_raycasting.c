/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:54:32 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/24 17:04:32 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3d.h"

int         swap(t_index *m, int i,int j)
{
    float   swap_x;
    float   swap_y;
    
    m->spr.sprite_dist = ((m->data.pos_x - m->spr.sprites_x[j]) *
    (m->data.pos_x - m->spr.sprites_x[j]) +
    (m->data.pos_y - m->spr.sprites_y[j]) * (m->data.pos_y - m->spr.sprites_y[j]));
    swap_x = m->spr.sprites_x[i];
    swap_y = m->spr.sprites_y[j];
    m->spr.sprites_x[i] = m->spr.sprites_x[i + 1];
    m->spr.sprites_y[i] = m->spr.sprites_y[i + 1];
    m->spr.sprites_x[i + 1] = swap_x;
    m->spr.sprites_y[i + 1] = swap_y;
}        
//sort sprites from far to close
int         sort_sprites(t_index *m)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < m->spr.numsprites - 1)
    {
        //sqrt not taken, unneeded
        m->spr.sprite_dist = ((m->data.pos_x - m->spr.sprites_x[i])
        * (m->data.pos_x - m->spr.sprites_x[i]) + (m->data.pos_y - m->spr.sprites_y[i]) 
        * (m->data.pos_y - m->spr.sprites_y[i]));
        j = i + 1;
        while (j < m->spr.numsprites - 1)
        {
            if (((m->data.pos_x - m->spr.sprites_x[j])
            * (m->data.pos_x - m->spr.sprites_x[j]) + (m->data.pos_y - m->spr.sprites_y[j]) 
            * (m->data.pos_y - m->spr.sprites_y[j])) > m->spr.sprite_dist)
            {
                swap(m, i, j);
            }
            j++;   
        }
        i++;
    }
}

int         sprite_raycasting(t_index *m)
{
    int i;
    
    i = 0;
    while(i < m->spr.numsprites)
    {
        sort_sprites(m);
        i++;
    }
    return (1);
}