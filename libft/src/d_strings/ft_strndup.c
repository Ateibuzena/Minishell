/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:09:20 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/10 17:09:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char *ft_strndup(const char *s1, size_t n)
{
    char *ptr;
    size_t len;

    if (!s1)
        return (NULL);
    
    // Determinar la longitud real a copiar
    len = ft_strlen(s1);
    if (len > n)
        len = n;

    // Reservar memoria
    ptr = malloc((len + 1) * sizeof(char));
    if (!ptr)
        return (NULL);
    
    // Copiar los caracteres
    ft_memcpy(ptr, s1, len);
    ptr[len] = '\0';  // Asegurarse de que esté null-terminada
    
    return (ptr);
}
