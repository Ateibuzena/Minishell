/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:35:09 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 22:01:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Elimina los caracteres especificados al principio y al final de una cadena.
 *
 * La función recorta la cadena `s1` eliminando los caracteres presentes en la cadena `set`
 * tanto al principio como al final de la cadena `s1`. Si no se encuentran caracteres de `set`
 * al principio o al final, se devuelve la cadena original.
 * Si la cadena resultante es vacía, se devuelve una cadena vacía.
 *
 * @param s1 La cadena de la cual se eliminarán los caracteres de `set`.
 * @param set La cadena que contiene los caracteres a eliminar de `s1`.
 *
 * @return Una nueva cadena con los caracteres de `set` eliminados al principio y al final.
 *         Si no se eliminan caracteres, se retorna la cadena original.
 *         Si la cadena resultante es vacía, se retorna una cadena vacía.
 */

#include "../../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	t_size	init;
	t_size	end;

	init = 0;
	end = ft_strlen(s1);
	while (s1[init] != '\0' && ft_strchr(set, s1[init]) != NULL)
		init++;
	if (s1[init] == '\0')
		return (ft_strdup(""));
	while (init < end && ft_strchr(set, s1[end]) != NULL)
	{
		end--;
	}
	end++;
	ptr = ft_substr(s1, init, end - init);
	return (ptr);
}

/*
#include <stdio.h>

int main(void)
{
    char    s1[20] = "aaaaaaaaxxxxcba";
    char    set[3] = "abc";
    char    *ptr;

    ptr = ft_strtrim(s1, set);
    printf("%s", ptr);
    return (0);
}
*/