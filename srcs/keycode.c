/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:19:51 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/14 17:13:38 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../Cub3d.h"


int		keys_up_down(t_index *m, int keycode)
{
	//move forward if no wall in front of you
	if (keycode == MLXK_W || keycode == MLXK_UP)
	{
		// calculate the future position of the coordinate x 
		if (m->parse.map[(int)m->data.pos_y][(int)(m->data.pos_x +
		m->data.dir_x * (m->data.move_speed + 0.1))] != '1')
		// update the x position
			m->data.pos_x += m->data.dir_x * m->data.move_speed;
		if (m->parse.map[(int)(m->data.pos_y + m->data.dir_y *
		(m->data.move_speed + 0.1))][(int)m->data.pos_x] != '1')
		// update the y position
			m->data.pos_y += m->data.dir_y * m->data.move_speed;
	}
	//move backwards if no wall behind you
	if (keycode == MLXK_S || keycode == MLXK_DOWN)
	{
		if (m->parse.map[(int)m->data.pos_y][(int)(m->data.pos_x -
		m->data.dir_x * (m->data.move_speed + 0.1))] != '1')
			m->data.pos_x -= m->data.dir_x * m->data.move_speed;
		if (m->parse.map[(int)(m->data.pos_y - m->data.dir_y *
		(m->data.move_speed + 0.1))][(int)m->data.pos_x] != '1')
			m->data.pos_y -= m->data.dir_y * m->data.move_speed;
	}
	return (1);
}

int		keys_rot1(t_index *m, int keycode)
{
	printf("rot1\n");
	if (keycode == MLXK_RIGHT)
	{
		m->data.old_dir_x = m->data.dir_x;
		m->data.dir_x = m->data.dir_x * cos(m->data.rot_speed) -
			m->data.dir_y * sin(m->data.rot_speed);
		m->data.dir_y = m->data.old_dir_x * sin(m->data.rot_speed) +
			m->data.dir_y * cos(m->data.rot_speed);
		m->data.old_plane_x = m->data.plane_x;
		m->data.plane_x = m->data.plane_x * cos(m->data.rot_speed) -
			m->data.plane_y * sin(m->data.rot_speed);
		m->data.plane_y = m->data.old_plane_x * sin(m->data.rot_speed) +
			m->data.plane_y * cos(m->data.rot_speed);
	}
	return (1);
}

int		keys_rot2(t_index *m, int keycode)
{
	printf("rot2\n");
	if (keycode == MLXK_LEFT)
	{
		m->data.old_dir_x = m->data.dir_x;
		m->data.dir_x = m->data.dir_x * cos(-m->data.rot_speed) -
			m->data.dir_y * sin(-m->data.rot_speed);
		m->data.dir_y = m->data.old_dir_x * sin(-m->data.rot_speed) +
			m->data.dir_y * cos(-m->data.rot_speed);
		m->data.old_plane_x = m->data.plane_x;
		m->data.plane_x = m->data.plane_x * cos(-m->data.rot_speed) -
			m->data.plane_y * sin(-m->data.rot_speed);
		m->data.plane_y = m->data.old_plane_x * sin(-m->data.rot_speed) +
			m->data.plane_y * cos(-m->data.rot_speed);
	}
	return (1);
}

int		keys_right_left(t_index *m, int keycode)
{
	printf("rot right left \n");
	if (keycode == MLXK_A)
	{
		if (m->parse.map[(int)(m->data.pos_y - m->data.dir_x *
		(m->data.move_speed + 0.1))][(int)m->data.pos_x] != '1')
			m->data.pos_y -= m->data.dir_x * m->data.move_speed;
		if (m->parse.map[(int)m->data.pos_y][(int)(m->data.pos_x +
		m->data.dir_y * (m->data.move_speed + 0.1))] != '1')
			m->data.pos_x += m->data.dir_y * m->data.move_speed;
	}
	if (keycode == MLXK_D)
	{
		if (m->parse.map[(int)(m->data.pos_y + m->data.dir_x *
		(m->data.move_speed + 0.1))][(int)m->data.pos_x] != '1')
			m->data.pos_y += m->data.dir_x * m->data.move_speed;
		if (m->parse.map[(int)m->data.pos_y][(int)(m->data.pos_x -
		m->data.dir_y * (m->data.move_speed + 0.1))] != '1')
			m->data.pos_x -= m->data.dir_y * m->data.move_speed;
	}
	return (1);
}

int		ft_key(int keycode, t_index *m)
{
	m->data.old_plane_x = m->data.plane_x;
	if (keycode == MLXK_ESC || keycode == MLXK_X)
		exit_all(m);
	keys_up_down(m, keycode);
	keys_rot1(m, keycode);
	keys_rot2(m, keycode);
	keys_right_left(m, keycode);
	mlx_clear_window(m->win.mlx_ptr, m->win.mlx_win);
	draw(m);
	return (0);
}

