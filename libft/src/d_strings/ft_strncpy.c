/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:14:23 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 22:00:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Copia hasta `n` caracteres de una cadena a otra.
 *
 * Esta función copia como máximo `n` caracteres desde la cadena `src` hacia `dest`. Si la longitud de `src` es menor
 * que `n`, el resto de `dest` se completa con caracteres nulos (`'\0'`). Si la longitud de `src` es mayor o igual que
 * `n`, solo se copian los primeros `n` caracteres de `src` en `dest`.
 *
 * @param dest El destino donde se copiarán los caracteres de `src`.
 * @param src La cadena de origen desde la cual se copiarán los caracteres.
 * @param n El número máximo de caracteres a copiar.
 *
 * @return La cadena de destino `dest` después de la copia.
 */

#include <stddef.h>

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}