/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:36:51 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:36:51 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, lens1);
	ft_memcpy(&strjoin[lens1], s2, lens2);
	strjoin[lens1 + lens2] = '\0';
	free(s1);
	free(s2);
	return (strjoin);
}
