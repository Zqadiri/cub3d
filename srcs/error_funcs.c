/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:13:22 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/03 17:39:39 by zqadiri          ###   ########.fr       */
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

int		write_error_floor(t_index *m, int i)
{
	if (m->el.elem[m->el.f_l][i] == '\0' ||
		m->el.elem[m->el.f_l][i] == ' ' ||
		!ft_isdigit(m->el.elem[m->el.f_l][++i]))
	{
		write(1, "Error\n", 6);
		write(1, "Wrong arguments\n", 16);
		exit_all(m);
	}
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

int		write_error_ceilling(t_index *m, int i)
{
	if (m->el.elem[m->el.c_l][i] == '\0' ||
		m->el.elem[m->el.c_l][i] == ' ' ||
		!ft_isdigit(m->el.elem[m->el.f_l][++i]))
	{
		write(1, "Error\n", 6);
		write(1, "Wrong ceilling arguments\n", 25);
		exit_all(m);
	}
	return (-1);
}

int		write_error_end_ceilling(t_index *m, int i)
{
	if (m->el.elem[m->el.c_l][i] != ' ')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong ceilling arguments\n", 25);
		exit_all(m);
	}
	return (-1);
}
