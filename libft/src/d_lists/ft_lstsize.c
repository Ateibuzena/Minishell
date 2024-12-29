/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:08:29 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:50:30 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstsize.c
 * @brief Obtiene el tamaño de la lista.
 *
 * Esta función recorre la lista y cuenta el número de nodos presentes.
 * 
 * @param lst La lista de nodos.
 * @return El número de nodos en la lista.
 */

#include "../../libft.h"

int	ft_lstsize(t_list_42 *lst)
{
	int		i;
	t_list_42	*sublist;

	i = 0;
	sublist = lst;
	while (sublist)
	{
		i++;
		sublist = sublist->next;
	}
	return (i);
}
