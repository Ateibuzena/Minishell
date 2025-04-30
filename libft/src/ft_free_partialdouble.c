/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_partialdouble.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:27:08 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/30 12:27:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_partialdouble(char **arr, int size)
{
	while (--size >= 0)
		free(arr[size]);
	free(arr);
}
