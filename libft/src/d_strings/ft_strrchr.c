/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:23:31 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 22:00:53 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Busca la última aparición de un carácter en una cadena.
 *
 * La función busca la última aparición del carácter `c` en la cadena `str`. Si se encuentra,
 * devuelve un puntero al primer carácter de esa aparición. Si el carácter no se encuentra en la cadena,
 * la función retorna `NULL`. Si el carácter es el carácter nulo (`'\0'`), se devuelve un puntero
 * al final de la cadena.
 *
 * @param str La cadena en la que se buscará el carácter.
 * @param c El carácter que se busca en la cadena.
 *
 * @return Un puntero al último carácter de la primera aparición de `c` en `str`,
 *         o `NULL` si el carácter no se encuentra.
 */

#include "../../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		len;
	char	*ptr;

	ptr = 0;
	len = ft_strlen(str);
	c = (unsigned char)c;
	while (len >= 0)
	{
		if (str[len] == c)
		{
			ptr = (char *)str + len;
			return (ptr);
		}
		len--;
	}
	if (c == '\0')
		ptr = (char *)str + ft_strlen(str);
	return (ptr);
}
