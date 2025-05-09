/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:41:49 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/07 14:21:36 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../historyft.h"

t_HistoryEntry	*ft_new_entry(const char *line)
{
	t_HistoryEntry	*entry;

	entry = (t_HistoryEntry *)malloc(1 * sizeof(t_HistoryEntry));
	if (!entry)
	{
		perror("minishell: Malloc Error");
		g_exit = 1;
	}
	entry->line = ft_strdup(line);
	entry->next = NULL;
	return (entry);
}

void	ft_init_history(t_History	*history)
{
	if (!history)
	{
		perror("minishell: Malloc Error");
		g_exit = 1;
	}
	history->tail = NULL;
	history->head = history->tail;
	history->size = 0;
}
