/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:50:08 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:27:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_puthex_lower(unsigned int i, int fd, int *count)
{
	char			*hex_digits;

	hex_digits = "0123456789abcdef";
	if (i >= 16)
		ft_puthex_lower((i / 16), fd, count);
	ft_putchar_printf(hex_digits[i % 16], fd, count);
}

void	ft_call_puthex_lower(va_list *args, int fd, int *count)
{
	unsigned int	i;

	i = va_arg(*args, unsigned int);
	ft_puthex_lower(i, fd, count);
}
