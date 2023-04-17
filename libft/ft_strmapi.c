/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:37:14 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:37:14 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fs;
	unsigned int	i;

	if (!s)
		return (NULL);
	fs = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!fs)
		return (NULL);
	i = 0;
	while (s[i])
	{
		fs[i] = f(i, s[i]);
		i++;
	}
	fs[i] = '\0';
	return (fs);
}
