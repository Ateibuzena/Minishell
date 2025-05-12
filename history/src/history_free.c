/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:58:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/12 22:04:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../historyft.h"

void	ft_free_history(t_History *history)
{
	t_HistoryEntry	*current;
	t_HistoryEntry	*next;

	if (!history)
		return ;
	current = history->head;
	while (current)
	{
		next = current->next;
		free(current->line);
		current->line = NULL;
		free(current);
		current = next;
	}
	history->head = NULL;
	history->tail = NULL;
	history->size = 0;
	free(history);
	history = NULL;
}
