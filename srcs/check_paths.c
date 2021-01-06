/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:31:27 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/06 12:46:30 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	trim_path_helper(t_index *m)
{
	int		i;
	char	*pfree;

	i = ft_strlen(m->el.east_path) - 1;
	while (is_white_space(m->el.east_path[i]))
		i--;
	pfree = m->el.east_path;
	if (!(m->el.east_path = ft_strndup(m->el.east_path, i + 1)))
		return (-1);
	free(pfree);
	i = ft_strlen(m->el.west_path) - 1;
	while (is_white_space(m->el.west_path[i]))
		i--;
	pfree = m->el.west_path;
	if (!(m->el.west_path = ft_strndup(m->el.west_path, i + 1)))
		return (-1);
	free(pfree);
	i = ft_strlen(m->el.spr_path) - 1;
	while (is_white_space(m->el.spr_path[i]))
		i--;
	pfree = m->el.spr_path;
	if (!(m->el.spr_path = ft_strndup(m->el.spr_path, i + 1)))
		return (-1);
	free(pfree);
	return (1);
}

int	trim_path(t_index *m)
{
	int		i;
	int		len;
	char	*pfree;

	len = ft_strlen(m->el.east_path);
	i = len - 1;
	while (is_white_space(m->el.north_path[i]))
		i--;
	pfree = m->el.north_path;
	if (!(m->el.north_path = ft_strndup(m->el.north_path, i + 1)))
		return (-1);
	free(pfree);
	len = ft_strlen(m->el.south_path);
	i = len - 1;
	while (is_white_space(m->el.south_path[i]))
		i--;
	pfree = m->el.south_path;
	if (!(m->el.south_path = ft_strndup(m->el.south_path, i + 1)))
		return (-1);
	free(pfree);
	return (1);
}
