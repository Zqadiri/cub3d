/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:33:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/01/25 19:14:56 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char		*create_new_line(char *str, int diff)
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

int			create_good_size_map(t_index *m)
{
	int		i;
	int		len;
	int		diff;
	char	*new;

	i = 0;
	len = new_strlen(m->parse.map[i]);
	while (m->parse.map[++i] != NULL)
	{
		if (new_strlen(m->parse.map[i]) > len)
			len = new_strlen(m->parse.map[i]);
	}
	i = -1;
	while (m->parse.map[++i] != NULL)
	{
		if (new_strlen(m->parse.map[i]) < len)
		{
			diff = len - new_strlen(m->parse.map[i]);
			new = m->parse.map[i];
			if (!(m->parse.map[i] = create_new_line(m->parse.map[i], diff)))
				return (-1);
			free(new);
		}
	}
	return (1);
}

void		check_elem_nbr(t_index *m)
{
	int i;

	i = -1;
	while (m->el.elem[++i] != '\0')
	{
		if (m->el.elem[i][0] == 'R' && m->el.elem[i][1] == ' ')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'N' && m->el.elem[i][1] == 'O')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'S' && m->el.elem[i][1] == 'O')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'S' && m->el.elem[i][1] == ' ')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'W' && m->el.elem[i][1] == 'E')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'E' && m->el.elem[i][1] == 'A')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'F' && m->el.elem[i][1] == ' ')
			m->parse.el_nbr++;
		else if (m->el.elem[i][0] == 'C' && m->el.elem[i][1] == ' ')
			m->parse.el_nbr++;
		else
			write_el_error(m, 2);
	}
	(m->parse.el_nbr != 8) ? write_el_error(m, 2) : 1;
}

int			check_valid_color(t_index *m)
{
	if (m->el.c_r < 0 || m->el.c_r > 255)
		write_el_error(m, 2);
	if (m->el.c_g < 0 || m->el.c_g > 255)
		write_el_error(m, 2);
	if (m->el.c_b < 0 || m->el.c_b > 255)
		write_el_error(m, 2);
	if (m->el.f_r < 0 || m->el.f_r > 255)
		write_el_error(m, 2);
	if (m->el.f_g < 0 || m->el.f_g > 255)
		write_el_error(m, 2);
	if (m->el.f_b < 0 || m->el.f_b > 255)
		write_el_error(m, 2);
	return (1);
}

int			create_map(t_index *m)
{
	treat_map(m, m->parse.map_str);
	if (!(m->parse.map = ft_split(m->parse.map_str, '\n')))
		return (-1);
	if (get_position(m) < 0)
		return (-1);
	if (check_borders_lines(m) < 0)
		return (-1);
	if (check_borders_columns(m) < 0)
		return (-1);
	if (create_good_size_map(m) < 0)
		return (-1);
	if (check_map_errors(m) < 0)
		return (-1);
	return (1);
}
