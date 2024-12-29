/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:52:45 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:42:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putnbr_fd.c
 * @brief Escribe un número entero en un archivo descriptor.
 *
 * Esta función escribe el número entero `n` en el archivo o descriptor de 
 * archivo indicado por `fd`. Si el número es negativo, primero escribe el 
 * signo negativo.
 * 
 * @param n El número entero a escribir.
 * @param fd El descriptor de archivo en el que se escribe el número.
 * 
 * @note La función maneja números negativos convirtiéndolos en positivos 
 *       antes de escribirlos, y utiliza recursión para escribir cada dígito.
 */

#include "../../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	char	c;

	i = n;
	if (i < 0)
	{
		write(fd, "-", 1);
		i = -i;
	}
	if (i / 10 != 0)
		ft_putnbr_fd(i / 10, fd);
	c = i % 10 + 48;
	write(fd, &c, 1);
}
