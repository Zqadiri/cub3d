/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:54:32 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/25 10:57:03 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3d.h"


void         swap(t_index *m, int i,int j)
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
void         sort_sprites(t_index *m)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < m->spr.numsprites - 1)
    {
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
void         update(t_index *m, int i)
{
    //translate sprite position to relative to camera
    m->spr.spr_x = m->spr.sprites_x[i] - m->data.pos_x;
    m->spr.spr_y = m->spr.sprites_y[i] - m->data.pos_y;
    //transform sprite with the inverse camera matrix
    // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
    // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
    // [ planeY   dirY ]                                          [ -planeY  planeX ]
    
    //required for correct matrix multiplication                                          [ -planeY  planeX ]
    m->spr.invdet = 1.0 / (m->data.plane_x * m->data.dir_y - m->data.dir_x * m->data.plane_y);
    m->spr.transform_x = m->spr.invdet * (m->data.dir_y * m->spr.spr_x - m->data.dir_x * m->spr.spr_y);
    m->spr.transform_y = m->spr.invdet * (-m->data.plane_y * m->spr.spr_x + m->data.plane_x * m->spr.spr_y);
    m->spr.spr_screen_x = (int)(m->el.res_x / 2) * (1 + m->spr.transform_x / m->spr.transform_y);
}


int         sprite_raycasting(t_index *m)
{
    int i;
    
    i = 0;
    //sort sprites from far to close
    sort_sprites(m);
    while(i < m->spr.numsprites)
    {
       //after sorting the sprites, do the projection and draw them
        update(m, i); 
        i++;
    }
    return (1);
}