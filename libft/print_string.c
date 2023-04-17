/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:28:18 by byanis            #+#    #+#             */
/*   Updated: 2023/01/03 20:21:08 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	handle_null(t_flags *flags)
{
	int	space;

	space = 0;
	if (!flags->precision && !flags->width)
	{
		ft_putstr_fd("(null)", 1);
		flags->ret += 6;
		return ;
	}
	if (flags->precision < 6 && !flags->width)
		return ;
	space = flags->width - 6;
	if (flags->width < 6)
		flags->ret += 6;
	else
		flags->ret += 6 + space;
	while (space-- > 0 && flags->width > 6)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd("(null)", 1);
}

static void	handle_string(t_flags *flags, char *str, int len)
{
	int		space;
	int		zero;

	zero = 0;
	space = 0;
	if (flags->width > len && flags->zero)
		zero = flags->width - len;
	if (flags->width > len && !zero)
		space = flags->width - len;
	flags->ret += len + space + zero;
	if (!flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	if (flags->zero)
		while (zero-- > 0)
			ft_putchar_fd('0', 1);
	while (len--)
		ft_putchar_fd(*str++, 1);
	if (flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}

void	print_string(va_list ap, t_flags *flags)
{
	char	*str;
	int		len;

	len = 0;
	str = va_arg(ap, char *);
	if (!str)
	{
		str = "(null)";
		handle_null(flags);
		return ;
	}
	if (flags->precision > 0 && flags->precision < (int)ft_strlen(str))
		len = flags->precision;
	else if (!(flags->dot && !flags->precision))
		len = ft_strlen(str);
	handle_string(flags, str, len);
}
