/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:59:10 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:38:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_tolower.c
 * @brief Convierte un carácter a minúscula.
 *
 * Esta función convierte un carácter alfabético en su versión en minúscula 
 * si es una letra mayúscula (A-Z). Si el carácter no es una letra mayúscula, 
 * se devuelve tal cual.
 * 
 * @param c El carácter a convertir, representado como un entero.
 * @return 
 *        - El carácter convertido a minúscula si es una letra mayúscula.
 *        - El mismo carácter si no es una letra mayúscula.
 * 
 * @note La función utiliza `ft_isalpha` para verificar si el carácter es 
 *       una letra antes de intentar convertirlo.
 * 
 * @see ft_isalpha
 */

#include "../../libft.h"

int	ft_tolower(int c)
{
	if (ft_isalpha(c) == 1 && (c >= 65 && c <= 90))
		return (c + 32);
	return (c);
}
