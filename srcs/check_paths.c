/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:31:27 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/13 18:49:04 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3d.h" 

void	calculate_colors(t_index *m)
{
	if (m->data.side == 1 && (m->data.map_y > m->data.pos_y))
		m->text.color = (int *)m->text.s_color;
	else if (m->data.side == 1 && (m->data.map_y < m->data.pos_y))
		m->text.color = (int *)m->text.n_color;
	else if (m->data.side == 0 && (m->data.map_x > m->data.pos_x))
		m->text.color = (int *)m->text.e_color;
	else
		m->text.color = (int *)m->text.w_color;
}

void	calculate_textures(t_index *m)
{
    //texturing calculations
	float	wallx;

    //calculate value of wallX
	if (m->data.side == 0)//where exactly the wall was hit
		wallx = m->data.pos_y + m->data.perp_wall_dist * m->data.ray_dir_y;
	else
		wallx = m->data.pos_x + m->data.perp_wall_dist * m->data.ray_dir_x;
	wallx -= floor((wallx));
    //x coordinate on the texture
	m->text.tex_x = (int)(wallx * m->text.tex_height);
	if (m->data.side == 0 && m->data.ray_dir_x > 0)
		m->text.tex_x = m->text.tex_width - m->text.tex_x - 1;
	if (m->data.side == 1 && m->data.ray_dir_y < 0)
		m->text.tex_x = m->text.tex_width - m->text.tex_x - 1;
    // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
    // How much to increase the texture coordinate per screen pixel
	m->text.step = 1.0 * m->text.tex_height / m->data.line_height;
    // Starting texture coordinate
	m->text.tex_pos = (m->data.draw_start - m->el.res_y / 2 + m->data.line_height / 2)
		* m->text.step;
}

