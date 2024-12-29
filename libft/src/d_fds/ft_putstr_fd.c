/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:46:22 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:43:00 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_putstr_fd.c
 * @brief Escribe una cadena en un archivo descriptor.
 *
 * Esta función escribe la cadena `s` en el archivo o descriptor de archivo 
 * indicado por `fd`.
 * 
 * @param s La cadena de caracteres a escribir.
 * @param fd El descriptor de archivo en el que se escribe la cadena.
 * 
 * @note La función utiliza la llamada al sistema `write` para escribir la cadena 
 *       en el archivo.
 */

#include "../../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
