/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:18:51 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:50:06 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstlast.c
 * @brief Obtiene el último nodo de la lista.
 *
 * Esta función recorre la lista hasta encontrar el último nodo (el nodo cuyo 
 * puntero `next` es NULL).
 * 
 * @param lst La lista de nodos.
 * @return El último nodo de la lista.
 */

#include "../../libft.h"

t_list_42	*ft_lstlast(t_list_42 *lst)
{
	t_list_42	*sublist;

	sublist = lst;
	while (sublist)
	{
		if (!sublist->next)
			return (sublist);
		sublist = sublist->next;
	}
	return (sublist);
}
