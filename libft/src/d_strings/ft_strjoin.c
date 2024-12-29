/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:33:23 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:58:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Une dos cadenas de caracteres en una nueva cadena.
 *
 * Esta función concatena las cadenas `s1` y `s2`, creando una nueva cadena
 * que contiene los caracteres de `s1` seguidos por los caracteres de `s2`.
 * La nueva cadena se devuelve, y su memoria es gestionada dentro de la función.
 *
 * @param s1 La primera cadena de caracteres a concatenar.
 * @param s2 La segunda cadena de caracteres a concatenar.
 * 
 * @return Una nueva cadena con los contenidos de `s1` y `s2` concatenados.
 *         Si hay un error en la asignación de memoria o si ambas cadenas son NULL,
 *         la función devuelve NULL.
 *
 * @note Si alguna de las cadenas de entrada es NULL, se trata de forma segura,
 *       y si ambas lo son, se devuelve NULL.
 */

#include "../../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*join;
	t_size		i;
	t_size		n;

	n = 0;
	i = 0;
	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	if (!s1 && !s2)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	while (n < ft_strlen(s2))
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = '\0';
	return (join);
}

/*The ft_strjoin function concatenates two strings
 s1 and s2 into a newly allocated string.
Parameters:
- s1: Pointer to the first string.
- s2: Pointer to the second string.
Return Value:
- A pointer to a newly allocated string which is 
the result of the concatenation of s1 and s2.
- If memory allocation fails, it returns NULL.
*/
