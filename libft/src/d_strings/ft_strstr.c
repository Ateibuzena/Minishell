/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:01:00 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/11 13:41:15 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char *ft_strstr(const char *haystack, const char *needle)
{
	const char *h;
	const char *n;

    if (!*needle)
        return ((char *)haystack);

    while (*haystack)
	{
        if (*haystack == *needle)
		{
            h = haystack;
            n = needle;
            while (*h && *n && *h == *n)
			{
                h++;
                n++;
            }
            if (!*n)
                return ((char *)haystack);
        }
		haystack++;
    }
    return (NULL);
}
