/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:39:22 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:42:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putchar_fd.c
 * @brief Escribe un carácter en un archivo descriptor.
 *
 * Esta función escribe un solo carácter `c` en el archivo o descriptor de 
 * archivo identificado por el descriptor `fd`.
 * 
 * @param c El carácter a escribir.
 * @param fd El descriptor de archivo en el que se escribe el carácter.
 * 
 * @note La función utiliza la llamada al sistema `write` para escribir el 
 *       carácter en el archivo.
 */

#include "../../libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
