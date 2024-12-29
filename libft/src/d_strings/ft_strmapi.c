/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:54:50 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:59:29 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Aplica una función a cada carácter de una cadena, pasando su índice y el carácter actual.
 *
 * Esta función recorre la cadena `s`, aplica la función `f` a cada carácter de la cadena junto con su índice, 
 * y devuelve una nueva cadena que contiene los resultados de la aplicación de la función a cada carácter.
 * La nueva cadena tiene el mismo tamaño que la original y se termina con un carácter nulo `\0`.
 *
 * @param s La cadena de caracteres sobre la que se aplicará la función.
 * @param f La función que se aplicará a cada carácter de la cadena. Recibe el índice y el carácter, y devuelve un nuevo carácter.
 *
 * @return Una nueva cadena de caracteres con los resultados de aplicar la función `f` a cada carácter de `s`.
 *         Si la memoria no se puede asignar, la función devuelve `NULL`.
 *
 * @note La memoria asignada para la nueva cadena debe ser liberada después de su uso para evitar fugas de memoria.
 */

#include "../../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	char	*temp;
	int		i;
	char	c;

	i = 0;
	ptr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	temp = ptr;
	while (s[i] != '\0')
	{
		c = f(i, s[i]);
		*temp = c;
		temp++;
		i++;
	}
	*temp = '\0';
	return (ptr);
}

/*
#include <stdio.h>
int main(void)
{
	char	ptr[20] = "hola ana que tal";
	char	*temp;

	temp = ft_strmapi(ptr, ft_f);
	printf("%s", temp);
	return (0);
}*/