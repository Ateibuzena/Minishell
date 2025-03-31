/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:00:10 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:02:43 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *hay, const char *need, t_size len)
{
	t_size	i;

	i = 0;
	if (len == (t_size)-1)
		len = ft_strlen(hay);
	if (*need == '\0')
		return ((char *)hay);
	while (*hay != '\0' && i < len)
	{
		if (*hay == *need)
		{
			if (ft_strncmp(hay, need, ft_strlen(need)) == 0
				&& len - i >= ft_strlen(need))
				return ((char *)hay);
		}
		hay++;
		i++;
	}
	return (0);
}

/* Locates the first occurrence of the null-terminated 
string need in the null-terminated string hay,
where not more than len characters are searched.
Parameters:
- hay: Pointer to the string to be searched.
- need: Pointer to the string to search for.
- len: Maximum number of characters to search within hay.
Returns:
- Pointer to the located string within hay, or NULL if the 
string is not found within the specified length. */
