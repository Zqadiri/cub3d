/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:12:17 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/24 21:48:08 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	val;
	int		i;

	i = ft_strlen(s);
	str = (char *)s;
	val = (char)c;
	while (i >= 0)
	{
		if (*str == val)
			return (str);
		str++;
		i--;
	}
	return (NULL);
}
