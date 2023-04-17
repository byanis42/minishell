/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:28:13 by byanis            #+#    #+#             */
/*   Updated: 2023/01/03 20:20:17 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

static void	ft_putnbr_base_long_fd(unsigned long int n, char *base, int fd)
{
	size_t	size_base;

	size_base = ft_strlen(base);
	if (n / size_base > 0)
		ft_putnbr_base_long_fd(n / size_base, base, fd);
	ft_putchar_fd(base[n % size_base], fd);
}

static int	ft_number_len(unsigned long int number, int base_size)
{
	size_t	len;

	len = 1;
	while (number / base_size > 0)
	{
		len++;
		number /= base_size;
	}
	return (len);
}

void	write_pointer(unsigned long int addr, int precision,
			int len, t_flags *flags)
{
	if (addr == 0)
	{
		write(1, "(nil)", 5);
		flags->ret += 2;
		return ;
	}
	write(1, "0x", 2);
	while (precision-- > 0)
		ft_putchar_fd('0', 1);
	if (len > 2)
		ft_putnbr_base_long_fd(addr, HEX_LOWER, 1);
}

static int	handle_space(int space, t_flags *flags, int len, int addr)
{
	if (addr == 0)
		space = flags->width - 5;
	else
		space = flags->width - len;
	if (addr == 0 && flags->width <= 4)
		flags->ret += 1;
	return (space);
}

void	print_pointer(va_list ap, t_flags *flags)
{
	unsigned long int	addr;
	int					len;
	int					space;
	int					precision;

	addr = va_arg(ap, unsigned long int);
	len = ft_number_len(addr, 16);
	precision = 0;
	space = 0;
	if (flags->precision > len)
		precision = flags->precision - len;
	if (!addr && flags->dot && !flags->precision)
		len = 2;
	else
		len += 2;
	if (flags->width > len)
		space = handle_space(space, flags, len, addr);
	flags->ret += len + space + precision;
	if (!flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
	write_pointer(addr, precision, len, flags);
	if (flags->minus)
		while (space-- > 0)
			ft_putchar_fd(' ', 1);
}
