/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:06:55 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:54:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Asigna memoria y la inicializa a cero.
 *
 * Esta función reserva un bloque de memoria del tamaño especificado y lo
 * inicializa a cero. La memoria reservada se libera mediante `free`.
 *
 * @param count El número de elementos a reservar.
 * @param size El tamaño de cada elemento.
 * @return Un puntero al bloque de memoria reservado e inicializado a cero,
 *         o NULL si la asignación falla.
 */

#include "../../libft.h"

void	*ft_calloc(t_size count, t_size size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
