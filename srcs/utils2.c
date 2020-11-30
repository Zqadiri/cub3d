/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:14:37 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/30 11:15:21 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int     new_strlen(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int     calcul_digit(t_index *m, int i)
{
	int digit;

	digit = 0;
	while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
	while (m->el.elem[m->el.resolution_line][i] >= '0' &&
		m->el.elem[m->el.resolution_line][i] <= '9')
	{
		digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
		i++;
	}
	m->el.res_x = digit;
	return (i);
}

void    init(t_index *m)
{
        init_1(m);
        init_2(m);
        init_3(m);
        init_4(m);
        init_5(m);
}
