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

#include "./Cub3d.h"


void	calculate_ray_pos_dir(int i, t_index *m)
{
	//calculate ray position and direction
	m->data.camera_x = 2 * i / (float)m->el.res_x - 1;//x-coordinate in camera space
	m->data.ray_dir_x = m->data.dir_x + m->data.plane_x * m->data.camera_x;
	m->data.ray_dir_y = m->data.dir_y + m->data.plane_y * m->data.camera_y;
	//which box of the map we're in
	m->data.map_x = m->data.pos_x;
	m->data.map_y = m->data.pos_y;
	//length of ray from one x or y-side to next x or y-side
	m->data.delta_dist_x = fabs(1 / m->data.ray_dir_x);
	m->data.delta_dist_y = fabs(1 / m->data.ray_dir_y);
}

void		

void	draw(t_index *m)
{
	int 	i;
	int 	hit; //was there a wall hit?

	i = 0;
	hit = 0;
	while (i < m->el.res_x)
	{
		hit = 0;

		calculate_ray_pos_dir(i, m);

		i++;
	}
	
}

int		launch_program(t_index *m, char *av)
{
	//printf("in 0\n");
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
	//raycast_algo(m);
	return (1);
}

int		main(int ac, char **av)
{
	t_index		m;

	if (ft_errors(ac, av) < 0)
		return (-1);
	else if (ac == 2)
	{
		//printf("in 3\n");
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
	}
	else
		exit_all(&m);
	return (0);
}