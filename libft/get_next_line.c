/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:08:41 by zqadiri           #+#    #+#             */
/*   Updated: 2020/10/23 19:37:08 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strduplicate(const char *src)
{
	int		size;
	char	*p;
	int		i;

	i = 0;
	size = 0;
	while (src[i] != '\0')
	{
		i++;
		size++;
	}
	size++;
	p = (char *)malloc(size * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		*(p + i) = src[i];
		i++;
	}
	*(p + i) = '\0';
	return (p);
}

char		*ft_join(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*p;
	int			size_s1;
	int			size_s2;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strln(s1);
	size_s2 = ft_strln(s2);
	p = malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (p)
	{
		while (s1[++i] != '\0')
			p[i] = s1[i];
		while (s2[j])
			p[i++] = s2[j++];
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}

int			get_next_line(int fd, char **line)
{
	static char		*save;
	int				r;
	char			*buff;
	char			*ptr;

	if (fd < 0 || !line || (!(buff = malloc(BUFFER_SIZE + 1))))
		return (-1);
	if (!save)
		save = ft_strduplicate("");
	while (!(ft_strchar(save, '\n')) && ((r = read(fd, buff, BUFFER_SIZE)) > 0))
	{
		buff[r] = '\0';
		ptr = save;
		save = ft_join(save, buff);
		free_ptr(&ptr, &ptr, 1, 0);
	}
	if (ft_strchar(save, '\n') != NULL)
	{
		*line = ft_substring(save, 0, ft_strlength(save));
		ptr = save;
		save = ft_strduplicate(save + ft_strlength(save) + 1);
		return (free_ptr(&ptr, &buff, 2, 1));
	}
	*line = ft_strduplicate(save);
	return (free_ptr(&save, &buff, 2, 0));
}
