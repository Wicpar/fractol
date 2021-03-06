/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:19:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/12 18:23:49 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstremove(t_list **alst)
{
	t_list *tmp;

	tmp = *alst;
	if (tmp)
	{
		*alst = tmp->next;
		tmp->next = 0;
	}
	return (tmp);
}
