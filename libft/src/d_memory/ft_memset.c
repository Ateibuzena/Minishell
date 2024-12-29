/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:57:54 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:55:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Establece un valor específico en un bloque de memoria.
 *
 * Esta función establece todos los bytes de un bloque de memoria apuntado
 * por `array` con el valor especificado por `value`. El valor es convertido
 * a un `unsigned char` antes de ser asignado.
 *
 * @param array Puntero al bloque de memoria a modificar.
 * @param value El valor a establecer en cada byte del bloque.
 * @param len La longitud del bloque de memoria.
 * @return El puntero al bloque de memoria modificado.
 */

#include "../../libft.h"

void	*ft_memset(void *array, int value, t_size len)
{
	t_size			i;	
	unsigned char	*ptr;

	ptr = (unsigned char *)array;
	i = 0;
	while (i < len)
	{
		*ptr = (unsigned char)value;
		i++;
		ptr++;
	}
	return (array);
}
