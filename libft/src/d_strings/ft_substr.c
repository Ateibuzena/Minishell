/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:42:11 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 22:01:43 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Extrae una subcadena de una cadena dada.
 *
 * La función `ft_substr` extrae una subcadena de la cadena `s`, comenzando en el índice
 * `start` y con una longitud máxima de `len` caracteres. Si la longitud de la cadena es menor
 * que el índice de inicio, se retorna una cadena vacía. Si la subcadena extraída es más corta
 * que `len`, se ajusta al tamaño disponible desde la posición `start` hasta el final de la cadena.
 *
 * @param s La cadena original de la cual se extraerá la subcadena.
 * @param start El índice de inicio desde donde comenzará la subcadena.
 * @param len La longitud máxima de la subcadena a extraer.
 *
 * @return Una nueva cadena con la subcadena extraída, o NULL si ocurre un error de asignación de memoria.
 *         Si el índice de inicio es mayor que la longitud de la cadena, se retorna una cadena vacía.
 */

#include "../../libft.h"

char	*ft_substr(char const *s, unsigned int start, t_size len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

/* Allocates and returns a substring of the string s.
The substring begins at index start and is of maximum size len.
Parameters:
- s: Pointer to the string.
- start: Index of the starting character of the substring.
- len: Maximum length of the substring.
Returns:
- Pointer to the newly allocated substring, or NULL if allocation fails. */
