/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:40:33 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 15:12:17 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_free(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (ptr);
}

char	*ft_free_staticbuffer(char *buffer)
{
	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
