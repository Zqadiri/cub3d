/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:47:24 by zqadiri           #+#    #+#             */
/*   Updated: 2020/12/03 10:51:59 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*get_sprite_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.sprite_line][i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.sprite_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.spr_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.sprite_line][i] != '\0')
	{
		m->el.spr_path[j] = m->el.elem[m->el.sprite_line][i];
		i++;
		j++;
	}
	m->el.spr_path[j] = '\0';
	return ("");
}

char	*get_north_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.north_line][i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.north_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.north_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.north_line][i] != '\0')
	{
		m->el.north_path[j] = m->el.elem[m->el.north_line][i];
		i++;
		j++;
	}
	m->el.north_path[j] = '\0';
	return ("");
}

char	*get_east_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.east_line][i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.east_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.east_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.east_line][i] != '\0')
	{
		m->el.east_path[j] = m->el.elem[m->el.east_line][i];
		i++;
		j++;
	}
	m->el.east_path[j] = '\0';
	return ("");
}

char	*get_west_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.west_line][i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.west_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.west_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.west_line][i] != '\0')
	{
		m->el.west_path[j] = m->el.elem[m->el.west_line][i];
		i++;
		j++;
	}
	m->el.west_path[j] = '\0';
	return ("");
}

char	*get_south_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.south_line][i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.south_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.south_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.south_line][i] != '\0')
	{
		m->el.south_path[j] = m->el.elem[m->el.south_line][i];
		i++;
		j++;
	}
	m->el.south_path[j] = '\0';
	return ("");
}
