/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:28:59 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:28:59 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_char(size_t count, char c)
{
	void	*ptr;
	size_t	mem;

	mem = count * sizeof(char);
	ptr = malloc(mem + 1);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, c, mem);
	return (ptr);
}
