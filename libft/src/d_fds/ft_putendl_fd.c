/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:49:21 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:42:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putendl_fd.c
 * @brief Escribe una cadena seguida de una nueva línea en un archivo descriptor.
 *
 * Esta función escribe la cadena `s` seguida de un salto de línea en el archivo 
 * o descriptor de archivo indicado por `fd`.
 * 
 * @param s La cadena de caracteres a escribir.
 * @param fd El descriptor de archivo en el que se escribe la cadena y la nueva línea.
 * 
 * @note La función utiliza la llamada al sistema `write` para escribir la cadena
 *       y luego un salto de línea.
 */

#include "../../libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
