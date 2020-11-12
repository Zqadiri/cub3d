/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:54:24 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/24 21:44:15 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	val;

	i = 0;
	ptr = (unsigned char *)src;
	val = (unsigned char)c;
	while (n-- > 0)
	{
		if (ptr[i] == val)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
