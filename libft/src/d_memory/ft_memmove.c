/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:41:48 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:55:07 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Mueve un bloque de memoria.
 *
 * Esta función copia los primeros `len` bytes desde el bloque de memoria
 * apuntado por `src` al bloque de memoria apuntado por `dst`, manejando de
 * manera segura los solapamientos de memoria. Si los bloques se solapan,
 * la copia se realiza de forma que no se pierdan datos.
 *
 * @param dst Puntero al destino de la copia.
 * @param src Puntero al origen de la copia.
 * @param len El número de bytes a mover.
 * @return El puntero a `dst`.
 */

#include "../../libft.h"

void	*ft_memmove(void *dst, const void *src, t_size len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	if (pdst == 0 && psrc == 0)
		return (0);
	if (pdst > psrc)
	{
		psrc += len;
		pdst += len;
		while (len--)
			*(--pdst) = *(--psrc);
	}
	else if (pdst < psrc)
	{
		while (len--)
			*(pdst++) = *(psrc++);
	}
	return (dst);
}

/* Copies len bytes from memory area src to memory area dst.
The memory areas may overlap.
Parameters:
- dst: Pointer to the destination memory area.
- src: Pointer to the source memory area.
- len: Number of bytes to copy.
Returns:
- Pointer to the destination memory area (dst). */
