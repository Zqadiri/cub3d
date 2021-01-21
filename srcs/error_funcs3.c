/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:43:04 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/19 14:33:51 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		write_error_one(t_index *m)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("Error in parsing\n", 1);
	return (exit_all(m));
}

int		write_error_end_ceilling(t_index *m, int i)
{
	if (m->el.elem[m->el.c_l][i] != ' ')
	{
		ft_putstr_fd("Error\n", 1);
		ft_putstr_fd("Wrong ceilling arguments\n", 1);
		exit_all(m);
	}
	return (-1);
}
