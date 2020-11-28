/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:20:07 by zqadiri           #+#    #+#             */
/*   Updated: 2020/10/19 23:20:07 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3d.h"

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

void		calculate_step_sidedist(t_index *m)
{
	if (m->data.ray_dir_x < 0)
	{
		m->data.step_x = -1;
		m->data.side_dist_x = (m->data.pos_x - m->data.map_x) 
		* m->data.delta_dist_x;
	}
	else
	{
		m->data.step_x = 1;
		m->data.side_dist_x = (m->data.map_x + 1.0 - m->data.pos_x) 
		* m->data.delta_dist_x;
	}
	if (m->data.ray_dir_y < 0)
	{
		m->data.step_y = -1;
		m->data.side_dist_y = (m->data.pos_y - m->data.map_y) 
		* m->data.delta_dist_y;
	}
	else 
	{
		m->data.step_y = 1;
		m->data.side_dist_y = (m->data.map_y + 1.0 - m->data.pos_y) 
		* m->data.delta_dist_y;
	}
}

/*
** jump to next map square, OR in x-direction,
** OR in y-direction & Check if ray has hit a wall
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

void	calculate_wall_height(t_index *m)
{
	/* Calculate height of line to draw on screen */
	m->data.wall_height = m->el.res_y;
	m->data.line_height = (int)(m->data.wall_height / m->data.perp_wall_dist);
	/* calculate lowest and highest pixel to fill in current stripe*/
	m->data.draw_start = -m->data.line_height / 2 + m->el.res_y / 2;
	if (m->data.draw_start < 0)
		m->data.draw_start = 0;
	m->data.draw_end = m->data.line_height / 2 + m->el.res_y / 2;
	if (m->data.draw_end >= m->el.res_y)
		m->data.draw_end = m->el.res_y - 1;
}

void		calculate_dist(t_index *m)
{
	/*Calculate distance projected on camera direction 
	 (Euclidean distance will give fisheye effect!)*/
	if (m->data.side == 0)
		m->data.perp_wall_dist = (m->data.map_x - m->data.pos_x +
		(1 - m->data.step_x) / 2) / m->data.ray_dir_x;
	else
		m->data.perp_wall_dist = (m->data.map_y - m->data.pos_y +
		(1 - m->data.step_y) / 2) / m->data.ray_dir_y;
	if (m->data.perp_wall_dist == 0)
		m->data.perp_wall_dist = 0.1;
}

void		draw(t_index *m)
{
	int		i;
	int		hit;

	i = 0;
	hit = 0;
	while (i < m->el.res_x)
	{
		hit = 0;
		calculate_ray_pos_dir(i, m);
		calculate_step_sidedist(m);
		perform_dda(m, hit);
		calculate_dist(m);
		calculate_wall_height(m);
		calculate_textures(m);
		calculate_colors(m);
		verline(i, m);
		m->spr.spr_buffer[i] = m->data.perp_wall_dist;
		i++;
	}
	sprite_raycasting(m);
	mlx_put_image_to_window(m->win.mlx_ptr, m->win.mlx_win, m->img.img, 0, 0);
}

int			launch_program(t_index *m, char *av)
{
	init(m);
	if (parse_cub(m, av) < 0)
		return (-1);
	if (!(m->win.mlx_ptr = mlx_init()))
		return (-1);
	m->win.mlx_win = mlx_new_window(m->win.mlx_ptr,
		m->el.res_x, m->el.res_y, WINDOW_TITLE);
	add_data(m);
	add_textures(m);
	m->img.img = mlx_new_image(m->win.mlx_ptr, m->el.res_x, m->el.res_y);
	m->img.addr = (int *)mlx_get_data_addr(m->img.img, &m->img.bits_per_pixel,
		&m->img.line_length, &m->img.endian);
	draw(m);
	return (1);
}

int			main (int ac, char **av)
{
	t_index		m;

	if (ft_errors(ac, av) < 0)
		return (-1);
	else if (ac == 2)
	{
		if ((launch_program(&m, av[1])) < 0)
			return (exit_all(&m));
		mlx_hook(m.win.mlx_win, 2, 1L << 1, ft_key, &m);
		mlx_hook(m.win.mlx_win, 17, 0, exit_all, &m);
		mlx_loop(m.win.mlx_ptr);
	}
	else if (ac == 3 && !ft_strncmp(av[2], "--save", 5))
	{
		if ((launch_program(&m, av[1])) < 0)
			return (exit_all(&m));
		if ((screen_shot(&m)) < 0)
			return (exit_all(&m));
	}
	else
		exit_all(&m);
	return (0);
}
