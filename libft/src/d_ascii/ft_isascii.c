/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:54:06 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:36:42 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isascii.c
 * @brief Verifica si un carácter pertenece al conjunto ASCII.
 *
 * Comprueba si el carácter proporcionado como argumento está dentro del rango
 * de caracteres ASCII estándar (valores entre 0 y 127).
 * 
 * @param c El carácter a comprobar, representado como un entero.
 * @return 
 *        - 1 si el carácter pertenece al conjunto ASCII.
 *        - 0 en caso contrario.
 */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
