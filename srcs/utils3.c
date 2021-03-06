/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 08:45:18 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/25 19:18:45 by zqadiri          ###   ########.fr       */
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
	m->el.res_x = digit;
	return (i);
}

int		check_line(char *s)
{
	int i;
	int no_digit;

	i = 0;
	no_digit = 0;
	if (digit(s))
		return (1);
	if (s[0] == '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (is_white_space(s[i]))
			return (-1);
		else
			i++;
	}
	return (1);
}

void	treat_map(t_index *m, char *str)
{
	int i;
	int start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			i++;
		else
		{
			start = 1;
			break ;
		}
	}
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n' && start)
			error_data(m, 4);
		i++;
	}
}
