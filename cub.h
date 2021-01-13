/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:50:34 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/13 11:52:57 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include "./libft/libft.h"

# define WINDOW_TITLE "cub3D"
# define MLXK_ESC 53
# define MLXK_X 17
# define MLXK_W 13
# define MLXK_A 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124

typedef struct			s_win
{
	void				*mlx_ptr;
	void				*mlx_win;
}						t_win;

typedef struct			s_image
{
	void				*img;
	int					*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct			s_elements
{
	char				**elem;
	int					resolution_line;
	unsigned long int	res_x;
	unsigned long int	res_y;
	int					north_line;
	int					south_line;
	int					west_line;
	int					east_line;
	int					sprite_line;
	int					f_l;
	int					c_l;
	int					c_r;
	int					c_g;
	int					c_b;
	int					f_r;
	int					f_g;
	int					f_b;
	int					c_color_hex;
	int					f_color_hex;
	char				*north_path;
	char				*south_path;
	char				*west_path;
	char				*east_path;
	char				*spr_path;
}						t_elements;

typedef struct			s_data
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				old_dir_x;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				camera_y;
	double				ray_dir_x;
	double				ray_dir_y;
	unsigned int		map_x;
	unsigned int		map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					draw_start;
	int					draw_end;
	int					wall_height;
	int					line_height;
	int					side;
	float				move_speed;
	float				rot_speed;
	double				old_plane_x;
}						t_data;

typedef struct			s_parse
{
	char				*data;
	char				*map_str;
	char				**map;
	int					line_nbr;
	int					column_nbr;
	double				x_pos_init;
	double				y_pos_init;
	char				dir;
	int					el_nbr;
	int					i;
	int					end;
	char				*line;
	int					ret;
	int					not_empty;
}						t_parse;

typedef struct			s_spr_xy
{
	double				x;
	double				y;
	double				dist;
}						t_spr_xy;

typedef struct			s_spr
{
	int					numsprites;
	int					spr_width;
	int					spr_height;
	double				*spr_buffer;
	void				*sprite_text;
	double				spr_x;
	double				spr_y;
	double				invdet;
	double				transform_x;
	double				transform_y;
	int					spr_screen_x;
	int					draw_start_y;
	int					draw_end_y;
	int					draw_start_x;
	int					draw_end_x;
	int					stripe;
	int					tex_x;
	int					tex_y;
	int					*color;
}						t_spr;

typedef struct			s_text
{
	int					tex_width;
	int					tex_height;
	void				*n_color;
	void				*s_color;
	void				*e_color;
	void				*w_color;
	int					tex_x;
	int					tex_y;
	double				tex_pos;
	int					*color;
	float				step;
}						t_text;

typedef struct			s_index
{
	t_win				win;
	t_image				img;
	t_data				data;
	t_parse				parse;
	t_elements			el;
	t_spr				spr;
	t_text				text;
	t_spr_xy			*s_xy;
}						t_index;
/*
** Error functions:
*/
int						exit_all(t_index *m);
int						ft_errors(int ac, char **av);
int						return_error_exit(t_index *m);
int						write_error_one(t_index *m);
int						return_error(t_index *m, int i);
int						write_el_error(t_index *m, int i);
int						write_error_end_floor(t_index *m, int i);
int						write_error_floor(t_index *m, int i);
int						write_error_end_ceilling(t_index *m, int i);
int						write_error_ceilling(t_index *m, int i);
int						check_north_and_south(t_index *m);
int						check_west_and_east(t_index *m);
int						check_elements_errors(t_index *m);
/*
** Init functions:
*/
void					init(t_index *m);
void					init_1(t_index *m);
void					init_2(t_index *m);
void					init_3(t_index *m);
void					init_4(t_index *m);
void					init_5(t_index *m);
/*
** Key rotation functions:
*/
int						ft_key(int keycode, t_index *m);
int						keys_right_left(t_index *m, int keycode);
int						keys_rot2(t_index *m, int keycode);
int						keys_rot1(t_index *m, int keycode);
int						keys_up_down(t_index *m, int keycode);
/*
** free:
*/
void					free_win(t_index *m);
void					free_map(t_index *m);
void					free_elem(t_index *m);
void					free_paths(t_index *m);
/*
** parsing functions:
*/
char					*get_north_texture(t_index *m);
char					*get_sprite_texture(t_index *m);
char					*get_south_texture(t_index *m);
char					*get_west_texture(t_index *m);
char					*get_east_texture(t_index *m);
int						get_sprites(t_index *m);
int						check_valid_color(t_index *m);
int						check_file_cub(char *filename);
int						launch_program(t_index *m, char *av);
int						parse_cub(t_index *m, char *filename);
int						parse_data(int fd, t_index *m);
int						parse_map(int fd, t_index *m, char *pfree);
int						check_elem_nbr(t_index *m);
int						create_map(t_index *m);
int						create_good_size_map(t_index *m);
char					*create_new_line(char *str, int diff);
int						check_map_errors(t_index *m);
int						check_spaces(t_index *m);
int						check_around(int i, int j, t_index *m);
int						check_dir_letter(t_index *m);
int						check_map_characters(t_index *m);
int						new_strlen(char *s);
void					create_hex_color(t_index *m);
int						transform_to_hex(int r, int g, int b);
int						calcul_digit(t_index *m, int i);
int						trim_path(t_index *m);
int						trim_path_helper(t_index *m);
int						check_resolution(t_index *m);
void					parse_sprites(t_index *m);
int						malloc_size_sprite(t_index *m);
int						get_ceilling_color(t_index *m);
int						get_floor_color(t_index *m);
int						get_resolution(t_index *m);
int						get_elements(t_index *m);
int						get_position(t_index *m);
int						get_position2(t_index *m, int i, int j);
int						check_borders_lines(t_index *m);
int						check_borders_columns(t_index *m);
int						check_letters(t_index *m, int i, int j);
int						add_data(t_index *m);
int						add_textures(t_index *m);
int						create_images(t_index *m);
int						create_images2(t_index *m);
int						create_elements_lines(t_index *m);
/*
** raycasting:
*/
void					sprite_raycasting(t_index *m);
void					sort_sprites(t_index *m);
void					order(t_index *m);
void					update(t_index *m, int i);
void					calculate_start_end(t_index *m);
void					draw_sprite(t_index *m);
void					verline(int i, t_index *m);
void					draw(t_index *m);
void					calculate_dist(t_index *m);
void					calculate_wall_height(t_index *m);
void					perform_dda(t_index *m, int hit);
void					calculate_step_sidedist(t_index *m);
void					calculate_ray_pos_dir(int i, t_index *m);
void					calculate_textures(t_index *m);
void					calculate_colors(t_index *m);
/*
**	utils:
*/
int						digit(char *c);
int						is_empty(char *s);
int						check_elem_nbr2(t_index *m, int i, int cpt);
void					clear(char *save, char *line);
int						is_white_space(char c);
int						error_data(t_index *m, int i);
int						exit_prg(t_index *m);
int						check_line(char *s);
/*
** bmp file:
*/
int						screen_shot(t_index *m);
int						write_info(t_index *m, int fd);
int						bit_map_file_headers(t_index *m, int fd, int file_size);

#endif
