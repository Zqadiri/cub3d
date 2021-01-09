/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:14:37 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/09 19:10:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		new_strlen(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int		is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	init(t_index *m)
{
	init_1(m);
	init_2(m);
	init_3(m);
	init_4(m);
	init_5(m);
}

void	clear(char *save, char *line)
{
	free(save);
	free(line);
	line = NULL;
}

int		is_empty(char *s)
{
	int i;

	if (!s)
		return (1);
	i = 0;
	if (s[0] == '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
