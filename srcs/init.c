/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:13:12 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/02 14:35:49 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_1(t_index *m)
{
	m->win.mlx_ptr = NULL;
	m->win.mlx_win = NULL;
	m->img.img = NULL;
	m->img.addr = NULL;
	m->img.bits_per_pixel = 0;
	m->img.line_length = 0;
	m->img.endian = 0;
	m->data.old_plane_x = 0;
	m->data.rot_speed = 0;
	m->data.move_speed = 0;
}

void	init_2(t_index *m)
{
	m->el.elem = NULL;
	m->el.resolution_line = 0;
	m->el.res_x = 0;
	m->el.res_y = 0;
	m->el.north_line = 0;
	m->el.south_line = 0;
	m->el.west_line = 0;
	m->el.east_line = 0;
	m->el.sprite_line = 0;
	m->el.f_l = 0;
	m->el.c_l = 0;
	m->el.c_r = 0;
	m->el.c_g = 0;
	m->el.c_b = 0;
	m->el.f_r = 0;
	m->el.f_g = 0;
	m->el.f_b = 0;
	m->el.c_color_hex = 0;
	m->el.f_color_hex = 0;
	m->el.north_path = NULL;
	m->el.south_path = NULL;
}

void	init_3(t_index *m)
{
	m->data.pos_x = 0;
	m->data.pos_y = 0;
	m->data.dir_x = 0;
	m->data.dir_y = 0;
	m->data.old_dir_x = 0;
	m->data.plane_x = 0;
	m->data.plane_y = 0;
	m->data.camera_x = 0;
	m->data.camera_y = 0;
	m->data.ray_dir_y = 0;
	m->data.ray_dir_x = 0;
	m->data.map_x = 0;
	m->data.map_y = 0;
	m->data.side_dist_x = 0;
	m->data.side_dist_y = 0;
	m->data.delta_dist_x = 0;
	m->data.delta_dist_y = 0;
	m->data.perp_wall_dist = 0;
	m->data.step_x = 0;
	m->data.step_y = 0;
	m->data.draw_start = 0;
	m->data.draw_end = 0;
	m->data.line_height = 0;
	m->data.wall_height = 0;
	m->data.side = 0;
}

void	init_4(t_index *m)
{
	m->parse.data = NULL;
	m->parse.map_string = NULL;
	m->parse.clean_map_str = NULL;
	m->parse.map = NULL;
	m->parse.line_nbr = 0;
	m->parse.column_nbr = 0;
	m->parse.x_pos_init = 0;
	m->parse.y_pos_init = 0;
	m->parse.dir = 0;
	m->spr.numsprites = 0;
	m->spr.spr_width = 0;
	m->spr.spr_height = 0;
	m->spr.spr_buffer = NULL;
	m->spr.sprite_text = NULL;
	m->spr.spr_x = 0;
	m->spr.spr_y = 0;
	m->spr.invdet = 0;
	m->spr.transform_x = 0;
	m->spr.transform_y = 0;
	m->spr.spr_screen_x = 0;
	m->spr.draw_start_y = 0;
	m->spr.order = NULL;
	m->spr.v_move_screen = 0;
	m->s_xy = NULL;
}

void	init_5(t_index *m)
{
	m->el.west_path = NULL;
	m->el.east_path = NULL;
	m->el.spr_path = NULL;
	m->spr.draw_end_y = 0;
	m->spr.draw_start_x = 0;
	m->spr.draw_end_x = 0;
	m->spr.tex_x = 0;
	m->spr.tex_y = 0;
	m->spr.color = NULL;
	m->spr.stripe = 0;
	m->text.tex_width = 0;
	m->text.tex_height = 0;
	m->text.n_color = NULL;
	m->text.s_color = NULL;
	m->text.e_color = NULL;
	m->text.w_color = NULL;
	m->text.tex_x = 0;
	m->text.tex_y = 0;
	m->text.tex_pos = 0;
	m->text.color = NULL;
	m->text.step = 0;
}
