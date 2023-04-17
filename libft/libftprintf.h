/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byanis <byanis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:39:04 by byanis            #+#    #+#             */
/*   Updated: 2023/01/03 19:37:54 by byanis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>

# define DEC "0123456789"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"

typedef struct s_flags {
	int			index;
	int			zero;
	int			minus;
	int			width;
	int			precision;
	int			dot;
	int			negative;
	int			ret;
}				t_flags;

int				ft_printf(const char *format, ...);
void			store_flags(const char *format, va_list ap, t_flags *flags);
void			print_char(va_list ap, t_flags *flags);
void			print_string(va_list ap, t_flags *flags);
void			print_diux(va_list ap, char c, t_flags *flags);
void			print_pointer(va_list ap, t_flags *flags);
void			print_percent(t_flags *flags);
void			handle_zero(t_flags *flags);

#endif
