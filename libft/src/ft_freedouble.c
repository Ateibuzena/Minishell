/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:10:52 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/17 19:53:47 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_freedouble(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
		}
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	ft_freedouble_array(int **array, int len)
{
	int		j;

	if (!array)
		return ;
	j = 0;
	while (j < len)
	{
		if (array[j])
		{
			free(array[j]);
			array[j] = 0;
		}
		j++;
	}
	free(array);
	array = 0;
}
