/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 08:45:18 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/08 08:58:35 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		check_file_cub(char *filename)
{
	int	i;

	i = ft_strlen(filename) - 1;
	if (filename[i] != 'b' || filename[i - 1] != 'u' ||
		filename[i - 2] != 'c' || filename[i - 3] != '.')
	{
		write(1, "Error\n", 6);
		write(1, "wrong file extention\n", 16);
		exit(0);
	}
	return (1);
}

int		calcul_digit(t_index *m, int i)
{
	unsigned long int digit;

	digit = 0;
	while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
	while (m->el.elem[m->el.resolution_line][i] >= '0' &&
		m->el.elem[m->el.resolution_line][i] <= '9')
	{
		digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
		i++;
	}
	m->el.res_x = (int)digit;
	return (i);
}
