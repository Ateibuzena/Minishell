/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:49:36 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:27:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putstr_printf(char *str, int fd, int *count)
{
	t_size	len;
	t_size	i;

	len = ft_strlen(str);
	i = len + 1;
	while (len)
	{
		ft_putchar_printf(str[(i - len) - 1], fd, count);
		len--;
	}
}

void	ft_call_putstr_printf(va_list *args, int fd, int *count)
{
	char	*str;

	str = (va_arg(*args, char *));
	if (!str)
		str = "(null)";
	ft_putstr_printf(str, fd, count);
}
