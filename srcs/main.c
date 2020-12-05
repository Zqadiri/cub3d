/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:12:32 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/05 18:10:26 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw(t_index *m)
{
	int	i;
	int	hit;

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

int		launch_program(t_index *m, char *av)
{
	// printf("launch\n");
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

int		main(int ac, char **av)
{
	t_index	m;

	// printf("%d", ac);

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
