/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:43:57 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:54:45 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compara dos bloques de memoria.
 *
 * Compara los primeros `n` bytes de los bloques de memoria apuntados por
 * `s1` y `s2`. La comparación se realiza byte por byte, y si los bloques
 * son diferentes, devuelve la diferencia entre los primeros bytes no iguales.
 *
 * @param s1 Puntero al primer bloque de memoria a comparar.
 * @param s2 Puntero al segundo bloque de memoria a comparar.
 * @param n El número de bytes a comparar.
 * @return 0 si los bloques son iguales, un valor negativo si `s1` es menor
 *         que `s2`, o un valor positivo si `s1` es mayor que `s2`.
 */

#include "../../libft.h"

int	ft_memcmp(const void *s1, const void *s2, t_size n)
{
	t_size			i;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	i = 0;
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	while (i < n)
	{
		if (*ptrs1 != *ptrs2)
			return (*ptrs1 - *ptrs2);
		ptrs1++;
		ptrs2++;
		i++;
	}
	return (0);
}
