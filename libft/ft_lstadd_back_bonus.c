/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:53:52 by zqadiri           #+#    #+#             */
/*   Updated: 2019/10/24 21:04:42 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **aslt, t_list *new)
{
	t_list		*last_lst;

	if (*aslt == NULL)
	{
		*aslt = new;
		return ;
	}
	last_lst = *aslt;
	ft_lstlast(last_lst);
	last_lst->next = new;
}
