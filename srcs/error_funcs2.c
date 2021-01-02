/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:29:07 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/02 10:10:59 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		write_error_res(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Wrong arguments\n", 16);
	return (exit_all(m));
}

int		write_el_error(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Wrong elements\n", 16);
	return (exit_all(m));
}

int		ft_errors(int ac, char **av)
{
	int fd;

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
