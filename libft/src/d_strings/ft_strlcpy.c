/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:09:03 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:58:50 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Copia una cadena de caracteres desde `src` hacia `dst`, asegurando que la cadena `dst` esté correctamente terminada en `\0`.
 *
 * La función copia hasta `dstsize - 1` caracteres de la cadena `src` a `dst`, y garantiza que la cadena `dst` esté siempre
 * terminada con el carácter nulo `\0`. Si `dstsize` es mayor que la longitud de `src`, se copia toda la cadena `src` en `dst`.
 * Si `dstsize` es menor o igual a la longitud de `src`, solo se copian `dstsize - 1` caracteres y se asegura que `dst`
 * esté correctamente terminada en `\0`.
 *
 * @param dst La cadena de destino a la que se copiará el contenido de `src`.
 * @param src La cadena de origen que se copiará a `dst`.
 * @param dstsize El tamaño máximo de la cadena `dst`, incluyendo el carácter nulo `\0`.
 *
 * @return La longitud de la cadena `src`.
 *         Si `dstsize` es 0, la función devuelve la longitud de `src` sin realizar ninguna copia.
 *
 * @note Si `dstsize` es menor o igual a la longitud de `src`, la cadena `dst` no contendrá la cadena completa de `src`,
 *       pero se garantiza que se copiarán los primeros `dstsize - 1` caracteres y la cadena `dst` estará correctamente terminada.
 */

#include "../../libft.h"

t_size	ft_strlcpy(char *dst, const char *src, t_size dstsize)
{
	t_size	i;
	t_size	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= srclen)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (srclen);
}

/* Copies the NUL-terminated string src to dst 
(including the NUL terminator)
up to a maximum of dstsize - 1 characters.
Parameters:
- dst: Pointer to the destination string.
- src: Pointer to the source string.
- dstsize: Size of the destination buffer.
Returns:
- Total length of the string that would have been created 
if there was enough space, excluding the NUL terminator. */
