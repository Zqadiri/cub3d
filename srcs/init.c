/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:24:35 by zqadiri           #+#    #+#             */
/*   Updated: 2020/10/22 12:24:35 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void init_1(t_index *m)
{
  m->img.img = NULL;
  m->img.addr = NULL;
  m->img.bits_per_pixel = 0;
  m->img.line_length = 0;
  m->img.endian = 0;
  m->win.mlx_ptr = NULL;
  m->win.mlx_win = NULL;
}

void	init_2(t_index *m)
{
  m->el.elem = NULL;
  m->el.resolution_line = 0;
  m->el.res_x = 0;
  m->el.res_y = 0;
  m->el.north_path = NULL;
  m->el.south_path = NULL;
  m->el.west_path = NULL;
  m->el.east_path = NULL;
  m->el.spr_path = NULL;
	m->el.north_line = 0;
	m->el.south_line = 0;
	m->el.west_line = 0;
	m->el.east_line = 0;
	m->el.sprite_line = 0;
	m->el.f_line = 0;
	m->el.c_line = 0;
	m->el.c_red = 0;
	m->el.c_green = 0;
	m->el.c_blue = 0;
	m->el.f_red = 0;
	m->el.f_green = 0;
	m->el.f_blue = 0;
	m->el.c_color_hex = 0;
	m->el.f_color_hex = 0;
}

void init_3(t_index *m)
{
  m->data.pos_x = 0;
  m->data.pos_y = 0;
  m->data.dir_x = 0;
  m->data.plane_x = 0;
  m->data.plane_y = 0;
  m->data.camera_x = 0;
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
  m->data.old_dir_x = 0;
	m->data.old_plane_x = 0;
  m->data.rot_speed = 0;
  m->data.move_speed = 0;
  m->pos.rotation_angle = 0;
  m->pos.ray_angle = 0;
}

void init_4(t_index  *m)
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
  m->spr.sprites_x = NULL;
  m->spr.sprites_y = NULL;
  m->spr.spr_width = 0;
  m->spr.spr_height = 0;
  m->spr.spr_buffer = NULL;
  m->spr.sprite_text = NULL;

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

void	init(t_index *m)
{
	init_1(m);
	init_2(m);
	init_3(m);
	init_4(m);
}