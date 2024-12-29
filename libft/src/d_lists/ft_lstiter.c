/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:38:24 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:49:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstiter.c
 * @brief Aplica una función a cada elemento de la lista.
 *
 * Esta función recorre la lista y aplica la función `f` a cada nodo de la lista.
 * 
 * @param lst La lista de nodos a recorrer.
 * @param f La función a aplicar a cada nodo de la lista.
 */

#include "../../libft.h"

void	ft_lstiter(t_list_42 *lst, void (*f)(void *))
{
	t_list_42	*sublist;

	sublist = lst;
	while (sublist)
	{
		f(sublist->content);
		sublist = sublist->next;
	}
}
