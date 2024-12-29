/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:47:45 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:59:09 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Calcula la longitud de una cadena de caracteres.
 *
 * La función recorre la cadena `s` hasta encontrar el carácter nulo `\0` que indica el final de la cadena,
 * y devuelve el número de caracteres antes de dicho carácter nulo.
 *
 * @param s La cadena de caracteres cuya longitud se va a calcular.
 *
 * @return La longitud de la cadena `s` (número de caracteres antes del carácter nulo).
 *
 * @note Si la cadena es vacía, es decir, si `s` apunta a una cadena que comienza con el carácter `\0`,
 *       la función devolverá 0.
 */

#include "../../libft.h"

t_size	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/* Calculates the length of the string s, excluding the terminating null byte.
Parameters:
- s: Pointer to the string.
Returns:
- Length of the string (number of characters) excluding the null terminator. */
