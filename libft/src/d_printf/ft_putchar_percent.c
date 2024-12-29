/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:48:37 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:27:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_call_putchar_percent(va_list *args, int fd, int *count)
{
	(void)args;
	write(fd, "%", 1);
	*count += 1;
}
