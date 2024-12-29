/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:43:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:50:14 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstmap.c
 * @brief Crea una nueva lista aplicando una función a cada elemento.
 *
 * Esta función recorre la lista y aplica la función `f` a cada elemento,
 * creando una nueva lista con los resultados. Si hay algún error en la creación
 * de un nodo, se elimina la lista resultante utilizando la función `del`.
 * 
 * @param lst La lista de nodos a recorrer.
 * @param f La función que se aplica a cada nodo para crear el nuevo contenido.
 * @param del Función para eliminar el contenido de un nodo en caso de error.
 * @return La nueva lista con los elementos modificados, o NULL si ocurre un error.
 */

#include "../../libft.h"

t_list_42	*ft_lstmap(t_list_42 *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_42	*nodo;
	void	*temp;
	t_list_42	*sublist;
	t_list_42	*new_list;

	sublist = lst;
	new_list = 0;
	if (!lst)
		return (0);
	while (sublist)
	{
		temp = f(sublist->content);
		nodo = ft_lstnew(temp);
		if (!nodo)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, nodo);
		sublist = sublist->next;
	}
	return (new_list);
}
