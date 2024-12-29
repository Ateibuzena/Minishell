/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:50:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:27:29 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putnbr_printf(long int i, int fd, int *count)
{
	if (i < 0)
	{
		ft_putchar_printf('-', fd, count);
		i = -i;
	}
	if (i / 10 != 0)
		ft_putnbr_printf((i / 10), fd, count);
	ft_putchar_printf((i % 10 + '0'), fd, count);
}

void	ft_call_putnbr_printf(va_list *args, int fd, int *count)
{
	long int	i;

	i = va_arg(*args, int);
	ft_putnbr_printf(i, fd, count);
}
