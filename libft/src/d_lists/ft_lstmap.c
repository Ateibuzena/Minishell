/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:43:18 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 18:54:30 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list_42	*ft_lstmap(t_list_42 *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list_42	*nodo;
	void		*temp;
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
