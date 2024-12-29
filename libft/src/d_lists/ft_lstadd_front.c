/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:40:00 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:49:11 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstadd_front.c
 * @brief Añade un nuevo nodo al principio de la lista.
 *
 * Esta función agrega el nodo `new` al principio de la lista apuntada por `lst`.
 * 
 * @param lst Apuntador al primer nodo de la lista.
 * @param new El nodo que se va a añadir al principio de la lista.
 */

#include "../../libft.h"

void	ft_lstadd_front(t_list_42 **lst, t_list_42 *new)
{
	new->next = *lst;
	*lst = new;
}
