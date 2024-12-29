/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:40:33 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:30:42 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_newnode(int fd)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->buffer = malloc(1 * sizeof(char));
	if (!node->buffer)
		ft_freenode(&node, fd);
	node->buffer[0] = '\0';
	node->next = NULL;
	return (node);
}

char	*ft_freenode(t_list **list, int fd)
{
	t_list	*actual;
	t_list	*previous;

	actual = *list;
	previous = NULL;
	while (actual && actual->fd != fd)
	{
		previous = actual;
		actual = actual->next;
	}
	if (!actual)
		return (NULL);
	if (previous)
		previous->next = actual->next;
	else
		*list = actual->next;
	if (actual->buffer)
		free(actual->buffer);
	free(actual);
	return (NULL);
}

/*ft_freenode:
Si prev es NULL, significa que el nodo a eliminar es el primer nodo 
de la lista. Por lo tanto, *list (el inicio de la lista) se actualiza 
para que apunte al siguiente nodo (current->next).
Si prev no es NULL, se actualiza el puntero next del nodo anterior 
(prev->next) para que apunte al siguiente nodo de current (current->next), 
efectivamente eliminando current de la lista.
*/
/*Por qué ft_remove_node recibe un doble puntero?
La función ft_remove_node recibe un doble puntero porque se necesita
modificar el puntero que apunta al inicio de la lista (list) si el nodo a 
eliminar es el primer nodo de la lista. Si solo se pasara un puntero simple,
no se podría modificar el puntero original que apunta a la lista.

En cambio, ft_remove_list no necesita modificar el puntero que apunta a la
lista, ya que solo se utiliza para recorrer la lista y liberar cada nodo. 
Por lo tanto, solo necesita un puntero simple.*/
