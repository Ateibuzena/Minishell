/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:30:33 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:37:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isprint.c
 * @brief Verifica si un carácter es imprimible.
 *
 * Comprueba si el carácter proporcionado como argumento es un carácter 
 * imprimible, incluidos los caracteres visibles y el espacio (códigos ASCII 
 * del 32 al 126).
 * 
 * @param c El carácter a comprobar, representado como un entero.
 * @return 
 *        - 1 si el carácter es imprimible.
 *        - 0 en caso contrario.
 * 
 * @note La función también verifica si el carácter pertenece al conjunto 
 *       ASCII utilizando `ft_isascii`.
 * 
 * @see ft_isascii
 */

#include "../../libft.h"

int	ft_isprint(int c)
{
	if (ft_isascii(c) != 0)
	{
		if (c >= 32 && c <= 126)
			return (1);
	}
	return (0);
}
