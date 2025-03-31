/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:06:06 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 18:54:02 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list_42	*ft_lstnew(void *ptr)
{
	t_list_42	*nodo;

	nodo = malloc(sizeof(t_list_42));
	if (!nodo)
		return (NULL);
	nodo->content = ptr;
	nodo->next = NULL;
	return (nodo);
}
