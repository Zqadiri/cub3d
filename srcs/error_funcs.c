/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:13:22 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/15 11:04:27 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		return_error_exit(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Map not surrounded by 1\n", 24);
	exit_all(m);
	return (-1);
}

int		write_error_floor(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Wrong floor arguments\n", 22);
	exit_all(m);
	return (-1);
}

int		write_error_end_floor(t_index *m, int i)
{
	if (m->el.elem[m->el.f_l][i] != ' ')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong arguments\n", 16);
		exit_all(m);
	}
	return (-1);
}

int		write_error_ceilling(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Wrong ceilling arguments\n", 25);
	exit_all(m);
	return (-1);
}

int		error_data(t_index *m, int i)
{
	write(1, "Error\n", 6);
	if (i == 1)
	{
		write(1, "*.cub is missing something\n", 27);
		exit_prg(m);
		return (-1);
	}
	if (i == 2)
	{
		write(1, "Element must be separated by empty lines\n", 42);
		exit_prg(m);
		return (-1);
	}
	if (i == 3)
	{
		write(1, "the map content has to be the last\n", 36);
		exit_prg(m);
		return (-1);
	}
	return (1);
}
