/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:29:19 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:48:31 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstadd_back.c
 * @brief Añade un nuevo nodo al final de la lista.
 *
 * Esta función agrega el nodo `new` al final de la lista apuntada por `lst`.
 * Si la lista está vacía, se establece `new` como el primer nodo de la lista.
 * 
 * @param lst Apuntador al primer nodo de la lista.
 * @param new El nodo que se va a añadir al final de la lista.
 * 
 * @note Si la lista está vacía, se actualiza el primer nodo de la lista con `new`.
 */

#include "../../libft.h"

void	ft_lstadd_back(t_list_42 **lst, t_list_42 *new)
{
	t_list_42	*sublist;

	sublist = *lst;
	if (!sublist)
	{
		*lst = new;
		return ;
	}
	while (sublist->next)
		sublist = sublist->next;
	sublist->next = new;
}
