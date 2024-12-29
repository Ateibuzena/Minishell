/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_nil.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:50:08 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:27:19 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_puthex_nil(unsigned long int i, int fd, int *count)
{
	char			*hex_digits;

	hex_digits = "0123456789abcdef";
	if (i == 0)
	{
		ft_putstr_printf("(nil)", fd, count);
		return ;
	}
	if (i >= 16)
		ft_puthex_nil((i / 16), fd, count);
	ft_putchar_printf(hex_digits[i % 16], fd, count);
}

void	ft_call_puthex_nil(va_list *args, int fd, int *count)
{
	void				*argument;

	argument = va_arg(*args, void *);
	if (argument)
		ft_putstr_printf("0x", 1, count);
	ft_puthex_nil((unsigned long int)argument, fd, count);
}
