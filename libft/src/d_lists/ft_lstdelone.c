/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:05:14 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/28 21:49:41 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_lstdelone.c
 * @brief Elimina un único nodo de la lista.
 *
 * Esta función elimina el nodo `lst` y libera su contenido usando la función `del`.
 * 
 * @param lst El nodo a eliminar.
 * @param del Función que se aplica al contenido del nodo para eliminarlo.
 */

#include "../../libft.h"

void	ft_lstdelone(t_list_42 *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
