/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:10:52 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:11:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_freedouble(char **ptr)
{
	int	i;

	i = 0;
	if (ptr[i])
	{
		while (ptr[i])
		{
			ptr[i] = NULL;
			free(ptr[i]);
			i++;
		}
		ptr = NULL;
		free(ptr);
	}
}

void	ft_freedouble_array(int **pipes, int len)
{
	int		j;

	j = 0;
	while (j < len)
	{
		free(pipes[j]);
		j++;
	}
	free(pipes);
}
