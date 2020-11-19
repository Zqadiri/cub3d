/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:45:33 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/17 17:58:25 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"


///////**** get elements line *******////////////////

int		create_elements_lines(t_index *m)
{
	int i;
	int j;

	i = 0;
	while (m->el.elem[i] != NULL)
	{
		//printf("###%s;;\n", m->el.elem[i]);
		j = 0;
		while (m->el.elem[i][j] != '\0')
		{
			if (check_letters(m, i, j) < 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		add_data(t_index *m)
{
	if (m->parse.dir == 'E')
	{
		m->data.plane_x = 0.0;
		m->data.plane_y = 0.66;
		m->data.dir_x = 1;
		m->data.dir_y = 0;
	}
	if (m->parse.dir == 'W')
	{
		m->data.plane_x = 0;
		m->data.plane_y = -0.66;
		m->data.dir_x = -1;
		m->data.dir_y = 0;
	}
	if (m->parse.dir == 'S')
	{
		m->data.plane_x = -0.66;
		m->data.plane_y = 0;
		m->data.dir_x = 0;
		m->data.dir_y = 1;
	}
	if (m->parse.dir == 'N')
	{
		m->data.plane_x = 0.66;
		m->data.plane_y = 0;
		m->data.dir_x = 0;
		m->data.dir_y = -1;
	}
	m->data.pos_x = m->parse.x_pos_init;
	m->data.pos_y = m->parse.y_pos_init;
	m->text.tex_width = 64;
	m->text.tex_height = 64;
	m->spr.spr_width = 0;
	m->spr.spr_height = 0;
	m->data.move_speed = 0.2;
	m->data.rot_speed = 0.06;
	//m->pos.rotation_angle = m->data.dir_x * m->data.rot_speed;
	if (!(m->spr.spr_buffer = malloc(sizeof(float *) * m->el.res_x + 1)))
		return (exit_all(m));
	return (1);
}

/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// TEXTURES ////////////////////////////////////


int		create_images2(t_index *m)
{
	if (!(m->text.e_color = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.east_path,
		&m->text.tex_width, &m->text.tex_height)))
	{
		write(1, "Error\n", 6);
		write(1, "east wrong path texture", 23);
		exit_all(m);
		return (exit_all(m));
	}
	if (!(m->spr.sprite_text = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.spr_path,
		&m->spr.spr_width, &m->spr.spr_height)))
	{
		write(1, "Error\n", 6);
		write(1, "texture of the sprite is wrong", 30);
		return (exit_all(m));
	}
	return (1);
}

int		create_images(t_index *m)
{
	/*The functions that create images mlx_xpm_file_to_image(), will
	return NULL if an error occurs. Otherwise they return a non-null
	pointer as an image identifier.*/
	
	if (!(m->text.n_color = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.north_path,
		&m->text.tex_width, &m->text.tex_width)))
	{
		write(1, "Error\n", 6);
		write(1, "north wrong path texture\n", 24);
		return (exit_all(m));
	}
	if (!(m->text.s_color = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.south_path,
		&m->text.tex_width, &m->text.tex_height)))
	{
		write(1, "Error\n", 6);
		write(1, "south wrong path texture", 24);
		return (exit_all(m));
	}
	if (!(m->text.w_color = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.west_path,
		&m->text.tex_width, &m->text.tex_height)))
	{
		write(1, "Error\n", 6);
		write(1, "west wrong path texture", 23);
		return (exit_all(m));
	}
	return (1);
}

int		add_textures(t_index *m)
{
	if (create_images(m) < 0)
		return (exit_all(m));
	if (create_images2(m) < 0)
		return (exit_all(m));

	/*mlx_get_data_addr returns a char * address that represents the begining 
	of the memory area where the image is stored.*/

	m->text.n_color = mlx_get_data_addr(m->text.n_color,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->text.s_color = mlx_get_data_addr(m->text.s_color,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->text.w_color = mlx_get_data_addr(m->text.w_color,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->text.e_color = mlx_get_data_addr(m->text.e_color,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->spr.sprite_text = mlx_get_data_addr(m->spr.sprite_text,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	return (0);
}

