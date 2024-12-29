/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:40:42 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:36:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isalnum.c
 * @brief Verifica si un carácter es alfanumérico.
 *
 * Esta función comprueba si el carácter proporcionado como argumento es 
 * un carácter alfabético (a-z, A-Z) o un dígito (0-9).
 * 
 * @param c El carácter a comprobar, representado como un entero.
 * @return 
 *        - 1 si el carácter es alfanumérico.
 *        - 0 en caso contrario.
 * 
 * @note Utiliza las funciones `ft_isalpha` y `ft_isdigit` para realizar 
 *       las comprobaciones.
 * 
 * @see ft_isalpha, ft_isdigit
 */

#include "../../libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) != 0 || ft_isdigit(c) != 0)
		return (1);
	return (0);
}
