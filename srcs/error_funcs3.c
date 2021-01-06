/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_funcs3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:43:04 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/06 12:53:07 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		write_error_one(t_index *m)
{
	write(1, "Error\n", 6);
	write(1, "Error in parsing\n", 17);
	return (exit_all(m));
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
