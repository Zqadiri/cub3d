/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:33:29 by zqadiri           #+#    #+#             */
/*   Updated: 2020/11/29 17:57:17 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*create_new_line(char *str, int diff)
{
	int		i;
	char	*new;

	i = 0;
	if (!(new = malloc(sizeof(char *) * (new_strlen(str) + diff + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	while (diff > 0)
	{
		new[i] = ' ';
		i++;
		diff--;
	}
	new[i] = '\0';
	return (new);
}

int		create_good_size_map(t_index *m)
{
	int i;
	int len;
	int diff;

	i = 0;
	diff = 0;
	len = new_strlen(m->parse.map[i]);
	while (m->parse.map[i] != NULL)
	{
		if (new_strlen(m->parse.map[i]) > len)
			len = new_strlen(m->parse.map[i]);
		i++;
	}
	i = 0;
	while (m->parse.map[i] != NULL)
	{
		if (new_strlen(m->parse.map[i]) < len)
		{
			diff = len - new_strlen(m->parse.map[i]);
			if (!(m->parse.map[i] = create_new_line(m->parse.map[i], diff)))
				return (-1);
		}
		i++;
	}
	return (1);
}

int		create_map(t_index *m)
{
	if (!(m->parse.map = ft_split(m->parse.map_string, '\n')))
		return (-1);
	if (get_position(m) < 0)
		return (-1);
	if (check_borders_lines(m) < 0)
		return (-1);
	if (check_borders_columns(m) < 0)
		return (-1);
	return (1);
}
