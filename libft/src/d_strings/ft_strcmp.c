/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:56:48 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/16 19:23:53 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compara dos cadenas de caracteres.
 *
 * Esta función compara dos cadenas de caracteres `s1` y `s2` carácter por
 * carácter. Si las cadenas son idénticas, la función devuelve 1. Si las
 * cadenas son diferentes, devuelve 0.
 *
 * @param s1 La primera cadena que se va a comparar.
 * @param s2 La segunda cadena que se va a comparar.
 * @return 1 si las cadenas son iguales, 0 si son diferentes.
 */

#include "../../libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!s1 || !s2)  // 💥 EVITA CRASH POR NULL
		return (0); // O devuelve un valor de error adecuado
    while (s1[i] && s2[j] && (s1[i] == s2[j]))
    {
        i++;
        j++;
    }
    if (s1[i] == '\0' && s2[j] == '\0')
        return (1);
    return (0);
}