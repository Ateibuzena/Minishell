/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:44:36 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:38:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_toupper.c
 * @brief Convierte un carácter a mayúscula.
 *
 * Esta función convierte un carácter alfabético en su versión en mayúscula 
 * si es una letra minúscula (a-z). Si el carácter no es una letra minúscula, 
 * se devuelve tal cual.
 * 
 * @param c El carácter a convertir, representado como un entero.
 * @return 
 *        - El carácter convertido a mayúscula si es una letra minúscula.
 *        - El mismo carácter si no es una letra minúscula.
 * 
 * @note La función utiliza `ft_isalpha` para verificar si el carácter es 
 *       una letra antes de intentar convertirlo.
 * 
 * @see ft_isalpha
 */

#include "../../libft.h"

int	ft_toupper(int c)
{
	if (ft_isalpha(c) == 1 && (c >= 97 && c <= 122))
		return (c - 32);
	return (c);
}
