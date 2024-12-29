/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:48:37 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:31:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putchar_printf(char c, int fd, int *count)
{
	write(fd, &c, 1);
	*count += 1;
}

void	ft_call_putchar_printf(va_list *args, int fd, int *count)
{
	char	c;

	c = (char)va_arg(*args, int);
	ft_putchar_printf(c, fd, count);
}
