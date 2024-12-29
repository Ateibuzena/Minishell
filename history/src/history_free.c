/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:58:26 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/29 14:41:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../historyft.h"

void	ft_free_history(t_History *history)
{
	t_HistoryEntry	*current;
	t_HistoryEntry	*next;

	current = history->head;
	while (current)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
	free(history);
}