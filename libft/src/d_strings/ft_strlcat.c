/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:53 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:58:23 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Concatena una cadena de caracteres al final de otra, asegurando que no se exceda el tamaño máximo de destino.
 *
 * La función concatena hasta `dstsize - 1` caracteres de la cadena `src` al final de la cadena `dst`, y garantiza que
 * la cadena resultante esté siempre terminada en `\0` (carácter nulo). Si la longitud de `dst` es mayor o igual a `dstsize`,
 * no se realiza la concatenación y la longitud total esperada de la cadena concatenada es `dstsize + srclen`.
 *
 * @param dst La cadena de destino a la que se le añadirá el contenido de `src`.
 * @param src La cadena de origen que se añadirá a `dst`.
 * @param dstsize El tamaño total disponible para la cadena `dst`.
 *
 * @return La longitud total de la cadena concatenada (es decir, la longitud de `dst` más la longitud de `src`).
 *         Si el tamaño de destino `dstsize` es menor o igual a la longitud de `dst`, la función devuelve `dstsize + srclen`.
 *
 * @note Si la longitud de `dst` es mayor o igual a `dstsize`, la concatenación no se realiza y la cadena `dst` se mantiene intacta.
 *       Si `dstsize` es menor que la longitud de `dst`, se devuelve `dstsize + srclen`.
 */

#include "../../libft.h"

t_size	ft_strlcat(char *dst, const char *src, t_size dstsize)
{
	t_size		i;
	t_size		dstlen;
	t_size		srclen;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	while (src[i] != '\0' && i < dstsize - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

/* Appends the NUL-terminated string src to the end of dst.
It will append at most dstsize - strlen(dst) - 1 bytes, 
NUL-terminating the result.
Parameters:
- dst: Pointer to the destination string.
- src: Pointer to the source string.
- dstsize: Maximum number of characters that can be written to dst.
Returns:
- Total length of the string that would have been created if 
there was enough space, excluding the NUL terminator. */
