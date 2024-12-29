/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:15:57 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:56:29 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Busca la primera aparición de un carácter en una cadena.
 *
 * Esta función busca la primera ocurrencia del carácter `c` en la cadena
 * `str`. Si encuentra el carácter, devuelve un puntero a su primera aparición.
 * Si el carácter no se encuentra, la función devuelve NULL.
 *
 * @param str La cadena en la que se busca el carácter.
 * @param c El carácter que se busca en la cadena. El valor de `c` se ajusta
 *          al rango de valores válidos (0-255).
 * @return Un puntero a la primera aparición de `c` en `str`, o NULL si
 *         no se encuentra.
 */

#include "../../libft.h"

char	*ft_strchr(const char *str, int c)
{
	t_size		i;
	t_size		len;
	char		*ptr;

	i = 0;
	c = c % 256;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (str[i] == c)
		{
			ptr = (char *)str + i;
			return (ptr);
		}
		i++;
	}
	ptr = 0;
	return (ptr);
}
