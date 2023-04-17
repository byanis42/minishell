/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:29:06 by byanis            #+#    #+#             */
/*   Updated: 2023/01/10 19:39:52 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mem;

	mem = count * size;
	if ((count > 65535 || size > 65535) && (size_t)-1 / count < size)
		return (NULL);
	ptr = malloc(mem);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, mem);
	return (ptr);
}
