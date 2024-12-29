/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:28:48 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:57:18 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Duplica una cadena de caracteres.
 *
 * Esta función asigna memoria dinámica para crear una copia de la cadena
 * de caracteres `s1` y la devuelve. La nueva cadena será terminada en
 * un carácter nulo (`'\0'`).
 *
 * @param s1 La cadena de caracteres que se va a duplicar.
 * @return Un puntero a la nueva cadena duplicada, o NULL si la memoria
 *         no puede ser asignada.
 */

#include "../../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc((ft_strlen(s1) + 1) * 1);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, ft_strlen(s1));
	ptr[ft_strlen(s1)] = '\0';
	return (ptr);
}

/* Duplicates a string s1.
Allocates memory for the duplicate string using malloc.
Copies the contents of s1 to the newly allocated memory 
using ft_memcpy.
Appends a null terminator to the end of the duplicate string.
Parameters:
- s1: Pointer to the string to be duplicated.
Returns:
- Pointer to the newly allocated duplicate string, 
or NULL if memory allocation fails. */
