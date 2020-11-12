/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:55:43 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/25 03:10:54 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t size_dst;
	size_t size_src;

	size_dst = ft_strlen(dst);
	size_src = ft_strlen((char *)src);
	if (size <= size_dst)
		return (size + size_src);
	i = 0;
	while (src[i] != '\0' && (size - 1) > size_dst + i)
	{
		dst[size_dst + i] = src[i];
		i++;
	}
	dst[size_dst + i] = '\0';
	return (size_dst + size_src);
}
