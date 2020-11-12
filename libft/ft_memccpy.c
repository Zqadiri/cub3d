/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:10:46 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/25 00:54:55 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	val;

	i = 0;
	val = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char *)src)[i] == val)
		{
			((unsigned char*)dest)[i] = ((unsigned char *)src)[i];
			return (&((unsigned char *)dest)[i + 1]);
		}
		else
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (NULL);
}
