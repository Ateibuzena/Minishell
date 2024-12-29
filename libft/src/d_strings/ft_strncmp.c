/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:50:28 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:59:49 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compara los primeros `n` caracteres de dos cadenas de caracteres.
 *
 * Esta función compara los caracteres de las cadenas `s1` y `s2` hasta un máximo de `n` caracteres o hasta que 
 * se encuentre un carácter nulo (`'\0'`). Si encuentra una diferencia antes de alcanzar `n` caracteres, devuelve
 * la diferencia entre los caracteres en el mismo índice de ambas cadenas. Si las cadenas son iguales hasta el 
 * número de caracteres comparados, devuelve 0.
 *
 * @param s1 La primera cadena a comparar.
 * @param s2 La segunda cadena a comparar.
 * @param n El número máximo de caracteres a comparar.
 *
 * @return Un valor negativo si el primer carácter diferente en `s1` es menor que en `s2`,
 *         un valor positivo si es mayor, o 0 si las cadenas son iguales hasta el número de caracteres comparados.
 */

#include "../../libft.h"

int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	t_size			i;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	i = 0;
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	while ((ptrs1[i] != '\0' || ptrs2[i] != '\0') && i < n)
	{
		if (ptrs1[i] != ptrs2[i])
			return (ptrs1[i] - ptrs2[i]);
		i++;
	}
	return (0);
}

/* Compares up to the first n characters of two strings s1 and s2.
Parameters:
- s1: Pointer to the first string.
- s2: Pointer to the second string.
- n: Maximum number of characters to compare.
Returns:
- An integer less than, equal to, or greater than zero if the first n characters
of s1 are found, respectively, to be less than, to match, or be greater than
the first n characters of s2. */
