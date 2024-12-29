/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:38:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:37:09 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isdigit.c
 * @brief Verifica si un carácter es un dígito decimal.
 *
 * Comprueba si el carácter proporcionado como argumento es un dígito 
 * decimal (0-9) comparando su valor ASCII.
 * 
 * @param c El carácter a comprobar, representado como un entero.
 * @return 
 *        - 1 si el carácter es un dígito decimal.
 *        - 0 en caso contrario.
 */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
