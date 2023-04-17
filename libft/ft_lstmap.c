/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:32:16 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:32:16 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*ft_lst;
	t_list	*elem_f;

	if (!lst)
		return (NULL);
	ft_lst = ft_lstnew((*f)(lst->content));
	if (!ft_lst)
		return (NULL);
	tmp = lst->next;
	while (tmp)
	{
		elem_f = ft_lstnew((*f)(tmp->content));
		if (!elem_f)
		{
			ft_lstclear(&ft_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&ft_lst, elem_f);
		tmp = tmp->next;
	}
	return (ft_lst);
}
