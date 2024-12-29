/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:29:53 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:49:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstclear.c
 * @brief Elimina todos los nodos de la lista y aplica una función de eliminación.
 *
 * Esta función recorre la lista y elimina cada nodo usando la función `del` proporcionada.
 * 
 * @param lst Apuntador al primer nodo de la lista.
 * @param del Función que se aplica a cada nodo para eliminar su contenido.
 * 
 * @note La función libera la memoria asociada a cada nodo, incluyendo su contenido.
 */

#include "../../libft.h"

void	ft_lstclear(t_list_42 **lst, void (*del)(void *))
{
	t_list_42	*buffer;

	while (*lst)
	{
		buffer = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = buffer;
	}
}
