/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:31:27 by byanis            #+#    #+#             */
/*   Updated: 2022/09/20 10:31:27 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int nbr)
{
	int		len;
	long	n;

	n = nbr;
	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*itoa;
	int		len;
	int		i;

	nbr = n;
	len = ft_nbrlen(nbr);
	itoa = ft_calloc(len + 1, sizeof(char));
	if (!itoa)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		itoa[i] = '-';
		nbr = nbr * -1;
		i++;
	}
	while (nbr / 10 > 0 && len > i)
	{
		itoa[len - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	itoa[i] = nbr % 10 + '0';
	return (itoa);
}
