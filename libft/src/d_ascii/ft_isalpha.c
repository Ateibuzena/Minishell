/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:57:04 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:36:11 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isalpha.c
 * @brief Verifica si un carácter es alfabético.
 *
 * Comprueba si el carácter proporcionado como argumento es una letra 
 * del alfabeto (mayúscula o minúscula: A-Z, a-z) comparando su valor ASCII.
 * 
 * @param c El carácter a comprobar, representado como un entero.
 * @return 
 *        - 1 si el carácter es alfabético.
 *        - 0 en caso contrario.
 */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
