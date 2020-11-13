/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3b.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:24:20 by zqadiri           #+#    #+#             */
/*   Updated: 2020/10/22 12:24:20 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./minilibx/mlx.h"


# define WINDOW_TITLE "cub3D"
# define MLXK_ESC 53
# define MLXK_X 17
# define MLXK_W 13
# define MLXK_A 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124
# define MLXK_UP 126
# define MLXK_DOWN 125
# define MLXK_TD 14
# define MLXK_TG 12



typedef struct		s_win
{
	void			*mlx_ptr;
	void			*mlx_win;
}					t_win;

typedef struct		s_image
{
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image;

typedef struct		s_elements
{
	char			**elem;
	int				resolution_line;
	int				res_x;
	int				res_y;
	int				north_line;
	int				south_line;
	int				west_line;
	int				east_line;
	int				sprite_line;
	int				f_line;
	int				c_line;
	int				c_red;
	int				c_green;
	int				c_blue;
	int				f_red;
	int				f_green;
	int				f_blue;
	int				c_color_hex;
	int				f_color_hex;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	char			*spr_path;
}					t_elements;

typedef struct		s_data
{
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	float			old_dir_x;
	float			plane_x;
	float			plane_y;
	float			camera_x;
	float			camera_y;
	float			ray_dir_x;
	float			ray_dir_y;
	unsigned int	map_x;
	unsigned int	map_y;
	
	//length of ray from current position to next x or y-side
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			perp_wall_dist;

	//what direction to step in x or y-direction (either +1 or -1)
	int				step_x;
	int				step_y;
	int				draw_start;
	int				draw_end;
	int				wall_height;
	int				line_height;
	int				side;
	float			move_speed;
	float			rot_speed;
	float			old_plane_x;


}					t_data;

/*typedef	struct 		s_pos
{
	float			rotation_angle;
	float			ray_angle;
	int				is_facing_up;
	int				is_facing_down;
	int				is_facing_right;
	int				is_facing_left;
	int				y_intercept;
	int				x_intercept;	
	int				y;
	int				x;
	int				ystep;
	int				xstep;	
	int				save_horiz_wall_hit_x;
	int				save_horiz_wall_hit_y;

}					t_pos;*/


typedef struct		s_parse
{
	char			*data;
	char			*map_string;
	char			*clean_map_str;
	char			**map;
	int				line_nbr;
	int				column_nbr;
	float			x_pos_init;
	float			y_pos_init;
	char			dir;
}					t_parse;

typedef struct		s_spr
{
	int				numsprites;
	float			*sprites_x;
	float			*sprites_y;
	float			rites_y;
	int				spr_width;
	int				spr_height;
	float			*spr_buffer;
	void			*sprite_text;
}					t_spr;

typedef struct		s_text
{
	int				tex_width;
	int				tex_height;
	void			*n_color;
	void			*s_color;
	void			*e_color;
	void			*w_color;
	int				tex_x;
	int				tex_y;
	float			tex_pos;
	int				*color;
	float			step;
}					t_text;

typedef struct		s_index
{
	t_win			win;
	t_image			img;
	t_data			data;
	t_parse			parse;
	t_elements		el;
	t_spr			spr;
	t_text			text;
	//t_pos			pos;

}					t_index;

//////////////////// keycode.c ///////////////////////

int		ft_key(int keycode, t_index *m);
int		keys_right_left(t_index *m, int keycode);
int		keys_rot2(t_index *m, int keycode);
int		keys_rot1(t_index *m, int keycode);
int		keys_up_down(t_index *m, int keycode);

//////////////////// init.c ///////////////////////

void	init(t_index *m);
void 	init_1(t_index *m);
void	init_2(t_index *m);
void 	init_3(t_index *m);
void 	init_4(t_index  *m);

//////////////////// main.c ///////////////////////

void	cast_ray(int hit, float angle, t_index *m);
void	cast_all_rays(t_index *m);
int		launch_program(t_index *m, char *av);

//////////////////// parsing.c ///////////////////////

int		parse_cub(t_index *m, char *filename);
int		parse_data(int fd, t_index *m);
int		parse_map(int fd, t_index *m);
int		check_elem_nbr(t_index *m);

//////////////////// parsing2.c ///////////////////////

int		create_map(t_index *m);
int		create_good_size_map(t_index *m);
char	*create_new_line(char *str, int diff);

//////////////////// free.c ///////////////////////

void	free_win(t_index *m);
void	free_map(t_index *m);
void	free_elem(t_index *m);
void	free_paths(t_index *m);

//////////////////// check_map.c ///////////////////////

int		check_map_errors(t_index *m);
int		check_spaces_algo(t_index *m);
int		check_around(int i, int j, t_index *m);
int		check_dir_letter(t_index *m);
int		check_map_characters(t_index *m);

//////////////////// utils.c ///////////////////////

int		new_strlen(char *s);
void	create_hex_color(t_index *m);
int		transform_to_hex(int r, int g, int b);
int		calcul_digit(t_index *m, int i);
int		exit_all(t_index *m);
int		exit_it(t_index *m);

//////////////////// error_funcs.c ///////////////////////

int		ft_errors(int ac, char **av);
int		return_error_exit(t_index *m);
int		write_error_one(t_index *m);
int		return_error(t_index *m);
int		error_map(t_index *m);
int		write_el_error(void);
int		write_error_res(void);
int		write_error_end_floor(t_index *m, int i);
int		write_error_floor(t_index *m, int i);
int		write_error_end_ceilling(t_index *m, int i);
int		write_error_ceilling(t_index *m, int i);

//////////////////// check_data.c ///////////////////////

int		check_north_and_south(t_index *m);
int		check_west_and_east(t_index *m);
int		check_elements_errors(t_index *m);
int		check_path(char *str);
int		check_resolution(t_index *m);

/////////////////// get_textures.c ///////////////////////

char	*get_north_texture(t_index *m);
char	*get_sprite_texture(t_index *m);
char	*get_south_texture(t_index *m);
char	*get_west_texture(t_index *m);
char	*get_east_texture(t_index *m);

/////////////////// sprites_data.c ///////////////////////

int		get_sprites(t_index *m);
void	parse_sprites(t_index *m);
int		malloc_size_sprite(t_index *m);

/////////////////// get_elements.c ///////////////////////

int		get_ceilling_color(t_index *m);
int		get_floor_color(t_index *m);
int		get_resolution(t_index *m);
int		get_elements(t_index *m);

/////////////////// check.c ///////////////////////

int		get_position(t_index *m);
int		get_position2(t_index *m, int i, int j);
int		check_borders_lines(t_index *m);
int		check_borders_columns(t_index *m);
int		check_letters(t_index *m, int i, int j);

/////////////////// add_data.c ///////////////////////

int		add_data(t_index *m);
int		add_textures(t_index *m);
int		create_images(t_index *m);
int		create_images2(t_index *m);
int		create_elements_lines(t_index *m);

/////////////raycasting.c/////////////

void	draw(t_index *m);
void	calculate_dist(t_index *m);
void	calculate_wall_height(t_index *m);
void	perform_dda(t_index *m, int  hit);
void	calculate_step_sidedist(t_index *m);
void	calculate_ray_pos_dir(int i, t_index *m);

#endif