/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:53:21 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:54:58 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Copia un bloque de memoria.
 *
 * Esta función copia los primeros `n` bytes del bloque de memoria apuntado
 * por `src` al bloque de memoria apuntado por `dst`. Si ambos bloques se
 * solapan, el comportamiento es indefinido.
 *
 * @param dst Puntero al destino de la copia.
 * @param src Puntero al origen de la copia.
 * @param n El número de bytes a copiar.
 * @return El puntero a `dst`.
 */

#include "../../libft.h"

void	*ft_memcpy(void *dst, const void *src, t_size n)
{
	t_size				i;
	unsigned char		*pdst;
	const unsigned char	*psrc;

	i = 0;
	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (pdst == 0 && psrc == 0)
		return (0);
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
