/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:28:07 by byanis            #+#    #+#             */
/*   Updated: 2023/01/02 16:47:57 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	print_percent(t_flags *flags)
{
	int	space;
	int	zero;

	zero = 0;
	space = 0;
	if (flags->width > 1 && flags->zero)
		zero = flags->width - 1;
	if (flags->width > 1 && !zero)
		space = flags->width - 1;
	flags->ret += 1 + zero + space;
	if (!flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	if (flags->zero)
		while (zero-- > 0)
			ft_putchar_fd('0', 1);
	ft_putchar_fd('%', 1);
	if (flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}
