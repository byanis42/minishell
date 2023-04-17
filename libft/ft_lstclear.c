/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:31:46 by byanis            #+#    #+#             */
/*   Updated: 2022/11/03 15:17:38 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_free;

	to_free = *lst;
	if (!lst || !*lst || !del)
		return ;
	while (to_free)
	{
		*lst = to_free->next;
		free(to_free);
		to_free = *lst;
	}
	*lst = NULL;
}
