/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:35:21 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:35:21 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dst_c;
	const char	*src_c;

	i = 0;
	dst_c = dst;
	src_c = src;
	if (!dst && !src)
		return (NULL);
	if (src_c < dst_c)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dst_c[i] = src_c[i];
		}
	}
	else
		ft_memcpy(dst_c, src_c, len);
	return (dst_c);
}
