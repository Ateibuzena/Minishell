/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:49:04 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:54:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Llena un bloque de memoria con ceros.
 *
 * Esta función establece todos los bytes del bloque de memoria apuntado por
 * `array` a cero. Se utiliza principalmente para inicializar arrays o
 * estructuras de datos a valores predeterminados.
 *
 * @param array Puntero al bloque de memoria a ser modificado.
 * @param len Longitud del bloque de memoria a modificar.
 */

#include "../../libft.h"

void	ft_bzero(void *array, t_size len)
{
	ft_memset(array, 0, len);
}
