/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:06:06 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:50:22 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstnew.c
 * @brief Crea un nuevo nodo de la lista.
 *
 * Esta función crea un nuevo nodo de la lista con el contenido `ptr` y 
 * establece su puntero `next` como NULL.
 * 
 * @param ptr El contenido a almacenar en el nuevo nodo.
 * @return El nuevo nodo creado.
 */

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
