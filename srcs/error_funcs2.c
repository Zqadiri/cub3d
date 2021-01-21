/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:29:07 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/19 14:33:15 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		write_el_error(t_index *m, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Wrong resolution\n", 1);
		return (exit_all(m));
	}
	if (i == 2)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Wrong elements\n", 1);
		return (exit_all(m));
	}
	return (1);
}

int		ft_errors(int ac, char **av)
{
	int fd;

	if (ac == 1 || ac > 3)
	{
		ft_putstr_fd("Error\nInvalid arguments\n", 1);
		return (-1);
	}
	else if (ac == 3 && (ft_strncmp(av[2], "--save", 6)))
	{
		ft_putstr_fd("Error\nInvalid option\n", 1);
		return (-1);
	}
	else if ((fd = open(av[1], O_RDONLY)) <= 0)
	{
		ft_putstr_fd("Error\nNo such file or directory\n", 1);
		return (-1);
	}
	return (1);
}

int		return_error(t_index *m, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Multiple initial positions\n", 1);
		return (exit_all(m));
	}
	if (i == 2)
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("No player found (N,S,W,E)\n", 1);
		return (exit_all(m));
	}
	return (1);
}
