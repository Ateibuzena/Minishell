
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:30:33 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:25:18 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_isspace.c
 * @brief Verifica si un carácter es un espacio en blanco.
 *
 * Comprueba si el carácter proporcionado como argumento es un espacio en 
 * blanco, incluyendo espacios, tabulaciones, saltos de línea y otros 
 * caracteres de espacio definidos en el estándar C.
 * 
 * @param c El carácter a comprobar, representado como un carácter (`char`).
 * @return 
 *        - `true` si el carácter es un espacio en blanco.
 *        - `false` en caso contrario.
 */

#include "../../libft.h"

bool ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}