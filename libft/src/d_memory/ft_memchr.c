/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:32:13 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:54:30 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Busca un valor específico en un bloque de memoria.
 *
 * Esta función recorre un bloque de memoria en busca de un byte cuyo valor
 * coincida con el especificado por `c`. Si lo encuentra, devuelve un puntero
 * a la primera aparición de dicho valor. Si no lo encuentra, devuelve NULL.
 *
 * @param s Puntero al bloque de memoria en el que buscar.
 * @param c El valor que se desea encontrar.
 * @param n El número de bytes a buscar.
 * @return Un puntero a la primera aparición del valor buscado, o NULL si no
 *         se encuentra.
 */

#include "../../libft.h"

void	*ft_memchr(const void *s, int c, t_size n)
{
	unsigned char	*ptr;
	t_size			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
		i++;
	}
	return (0);
}
