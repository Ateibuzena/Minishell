/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:53:21 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 18:55:17 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memcpy(void *dst, const void *src, t_size n)
{
	t_size				i;
	unsigned char		*pdst;
	const unsigned char	*psrc;

	i = 0;
	pdst = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (pdst == 0 && psrc == 0)
		return (0);
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
