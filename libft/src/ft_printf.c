/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:48:37 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:28:55 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_Specifier	*ft_estructure(void)
{
	t_Specifier	*format_specifiers;

	format_specifiers = (t_Specifier *)malloc(9 * sizeof(t_Specifier));
	if (!format_specifiers)
		return (NULL);
	format_specifiers[0].key = 'c';
	format_specifiers[0].ft_ft = ft_call_putchar_printf;
	format_specifiers[1].key = 's';
	format_specifiers[1].ft_ft = ft_call_putstr_printf;
	format_specifiers[2].key = 'p';
	format_specifiers[2].ft_ft = ft_call_puthex_nil;
	format_specifiers[3].key = 'd';
	format_specifiers[3].ft_ft = ft_call_putnbr_printf;
	format_specifiers[4].key = 'i';
	format_specifiers[4].ft_ft = ft_call_putnbr_printf;
	format_specifiers[5].key = 'u';
	format_specifiers[5].ft_ft = ft_call_putnbr_u;
	format_specifiers[6].key = 'x';
	format_specifiers[6].ft_ft = ft_call_puthex_lower;
	format_specifiers[7].key = 'X';
	format_specifiers[7].ft_ft = ft_call_puthex_upper;
	format_specifiers[8].key = '%';
	format_specifiers[8].ft_ft = ft_call_putchar_percent;
	return (format_specifiers);
}

int	ft_printf(char const *format, ...)
{
	va_list		args;
	t_Printf	print;

	va_start(args, format);
	print.specifier = ft_estructure();
	if (!print.specifier)
		return (0);
	print.count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			print.i = -1;
			while (++print.i < 9)
				if (print.specifier[print.i].key == *format)
					print.specifier[print.i].ft_ft(&args, 1, &print.count);
		}
		else
			ft_putchar_printf(*format, 1, &print.count);
		format++;
	}
	free(print.specifier);
	va_end(args);
	return (print.count);
}
