/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:13:22 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/26 12:21:26 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		return_error_exit(t_index *m)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Invalid arguments\n", 1);
	exit_all(m);
	return (-1);
}

int		write_error_floor(t_index *m)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Wrong floor arguments\n", 1);
	exit_all(m);
	return (-1);
}

int		write_error_end_floor(t_index *m, int i)
{
	if (m->el.elem[m->el.f_l][i] != ' ')
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Wrong arguments\n", 1);
		exit_all(m);
	}
	return (-1);
}

int		write_error_ceilling(t_index *m)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Wrong ceilling arguments\n", 1);
	exit_all(m);
	return (-1);
}

int		error_data(t_index *m, int i)
{
	ft_putstr_fd("Error\n", 1);
	if (i == 1)
	{
		ft_putstr_fd("invalid config file\n", 1);
		exit_prg(m);
		return (-1);
	}
	if (i == 2)
	{
		ft_putstr_fd("Element must be separated by empty lines\n", 1);
		exit_prg(m);
		return (-1);
	}
	if (i == 4)
	{
		ft_putstr_fd("invalid map\n", 1);
		exit_all(m);
		return (-1);
	}
	return (1);
}
