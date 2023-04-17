/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:36:47 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:36:47 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	lenplus;

	lenplus = ft_strlen(s1) + 1;
	s2 = malloc(lenplus * sizeof(char));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, lenplus);
	return (s2);
}
