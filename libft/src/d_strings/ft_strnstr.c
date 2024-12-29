/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:00:10 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 22:00:29 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Busca la primera aparición de una subcadena dentro de una cadena,
 *        considerando una longitud máxima de búsqueda.
 *
 * La función busca la primera aparición de la cadena `need` dentro de la cadena `hay`, 
 * considerando solo los primeros `len` caracteres de `hay`. Si `need` está vacío,
 * la función devuelve la cadena `hay` completa. Si la subcadena `need` no se encuentra,
 * la función retorna `NULL`.
 *
 * @param hay La cadena en la que se realizará la búsqueda.
 * @param need La subcadena que se busca dentro de `hay`.
 * @param len La longitud máxima de caracteres de `hay` en la que buscar.
 *
 * @return Un puntero al primer carácter de la primera aparición de `need` en `hay`,
 *         o `NULL` si no se encuentra.
 */

#include "../../libft.h"

char	*ft_strnstr(const char *hay, const char *need, t_size len)
{
	t_size	i;

	i = 0;
	if (len == (t_size)-1)
		len = ft_strlen(hay);
	if (*need == '\0')
		return ((char *)hay);
	while (*hay != '\0' && i < len)
	{
		if (*hay == *need)
		{
			if (ft_strncmp(hay, need, ft_strlen(need)) == 0
				&& len - i >= ft_strlen(need))
				return ((char *)hay);
		}
		hay++;
		i++;
	}
	return (0);
}

/* Locates the first occurrence of the null-terminated 
string need in the null-terminated string hay,
where not more than len characters are searched.
Parameters:
- hay: Pointer to the string to be searched.
- need: Pointer to the string to search for.
- len: Maximum number of characters to search within hay.
Returns:
- Pointer to the located string within hay, or NULL if the 
string is not found within the specified length. */
