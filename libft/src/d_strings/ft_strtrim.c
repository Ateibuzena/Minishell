/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:35:09 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:07:11 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	t_size	init;
	t_size	end;

	init = 0;
	end = ft_strlen(s1);
	while (s1[init] != '\0' && ft_strchr(set, s1[init]) != NULL)
		init++;
	if (s1[init] == '\0')
		return (ft_strdup(""));
	while (init < end && ft_strchr(set, s1[end]) != NULL)
	{
		end--;
	}
	end++;
	ptr = ft_substr(s1, init, end - init);
	return (ptr);
}
