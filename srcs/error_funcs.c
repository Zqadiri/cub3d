/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:13:22 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/10 12:21:51 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int		write_error_res(void)
{
	write(1, "Error\n", 6);
	write(1, "Wrong arguments\n", 16);
	exit(0);
	return (-1);
}

int		write_el_error(void)
{
	write(1, "Error\n", 6);
	write(1, "Wrong elements\n", 16);
	exit(0);
	return (-1);
}

int		ft_errors(int ac, char **av)
{
	int fd;
	//printf("ac value = %d*\n", ac);
	//printf("av value = %s*\n", av[1]);

	if (ac == 1 || ac > 3)
	{
		write(1, "Error\nInvalid arguments\n", 24);
		return (-1);
	}
	else if (ac == 3 && (ft_strncmp(av[2], "--save", 6)))
	{
		write(1, "Error\nInvalid option\n", 21);
		return (-1);
	}
	else if ((fd = open(av[1], O_RDONLY)) <= 0)
	{
		write(1, "Error\nNo such file or directory\n", 32);
		return (-1);
	}
	return (1);
}

int		return_error(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Multiple initial positions\n", 27);
	return (exit_all(m));
}

int		write_error_one(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Error in parsing\n", 17);
	return (exit_all(m));
}

int		return_error_exit(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Map not surrounded by 1\n", 24);
	exit_all(m);
	return (-1);
}
int		error_map(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "No map included\n", 17);
	exit(0);
	return (-1);
}

int		write_error_floor(t_index *m, int i)
{
	if (m->el.elem[m->el.f_line][i] == '\0' ||
		m->el.elem[m->el.f_line][i] == ' '|| !ft_isdigit(m->el.elem[m->el.f_line][++i]))
	{
		write(1, "Error\n", 6);
		write(1, "Wrong arguments\n", 16);
		exit_all(m);
	}
	return (-1);
}

int		write_error_end_floor(t_index *m, int i)
{
	if (m->el.elem[m->el.f_line][i] != ' ')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong arguments\n", 16);
		exit_all(m);
	}
	return (-1);
}

int		write_error_ceilling(t_index *m, int i)
{
	if (m->el.elem[m->el.c_line][i] == '\0' ||
		m->el.elem[m->el.c_line][i] == ' '|| !ft_isdigit(m->el.elem[m->el.f_line][++i]))
	{
		write(1, "Error\n", 6);
		write(1, "Wrong ceilling arguments\n", 25);
		exit_all(m);
	}
	return (-1);
}

int		write_error_end_ceilling(t_index *m, int i)
{
	if (m->el.elem[m->el.c_line][i] != ' ')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong ceilling arguments\n", 25);
		exit_all(m);
	}
	return (-1);
}
