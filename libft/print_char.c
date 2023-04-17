/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:27:58 by byanis            #+#    #+#             */
/*   Updated: 2023/01/03 15:50:49 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

void	print_char(va_list ap, t_flags *flags)
{
	char	c;
	int		space;

	c = va_arg(ap, int);
	if (flags->width > 1)
		space = flags->width - 1;
	else
		space = 0;
	flags->ret += 1 + space;
	if (!flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	ft_putchar_fd(c, 1);
	if (flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}
