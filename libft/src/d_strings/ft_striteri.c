/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:22:51 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:57:37 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Aplica una función a cada carácter de una cadena.
 *
 * Esta función recorre la cadena de caracteres `s` y aplica la función
 * `f` a cada uno de sus caracteres, pasando el índice del carácter y
 * la dirección del carácter actual a la función `f`.
 *
 * @param s La cadena de caracteres sobre la que se aplicará la función.
 * @param f La función a aplicar a cada carácter de la cadena. Recibe dos
 *          parámetros: el índice del carácter y un puntero al carácter.
 * 
 * @note La función `f` debe ser definida por el usuario y debe aceptar
 *       dos parámetros: un índice de tipo `unsigned int` y un puntero
 *       a un carácter de tipo `char*`.
 */

#include "../../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>
int	main(void)
{
	char	s[20] = "hola";
	ft_striteri(s, ft_ff);
	printf("%s", s);
	return (0);
}*/