/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:48:47 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/11 15:22:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../historyft.h"

void	ft_add_entry(t_History *history, const char *line)
{
	t_HistoryEntry	*entry;

	if (!history || !line)
		return ;
	entry = ft_new_entry(line);
	if (!entry)
		return ;
	if (history->tail)
	{
		history->tail->next = entry;
		history->tail = entry;
	}
	else
	{
		history->tail = entry;
		history->head = entry;
	}
	history->size++;
	add_history(line);
}

void	ft_show_history(t_History *history)
{
	t_HistoryEntry	*current;
	int				i;

	current = history->head;
	printf("\nCommand history\n");
	i = 1;
	while (current)
	{
		printf("%d: %s\n", i, current->line);
		current = current->next;
		i++;
	}
}

char	*ft_navigate_history(t_History *history, int *index, int key)
{
	static t_HistoryEntry	*current;

	if (!current)
		current = NULL;
	if (!current)
	{
		current = history->tail;
		(*index) = history->size;
	}
	if (key == 1 && current && current->next)
	{
		current = current->next;
		(*index)++;
	}
	else if (key == -1 && current && current->next)
	{
		current = current->next;
		(*index)--;
	}
	if (current)
		return (current->line);
	return (NULL);
}

/*La variable estática es necesaria en esta función
para mantener el estado de navegación por el historial
entre diferentes llamadas a la función*/
/*La función ft_navigate_history se utiliza para navegar
hacia adelante o hacia atrás en el historial de comandos,
por ejemplo, al presionar las teclas ↑ (hacia atrás)
y ↓ (hacia adelante). Para que la navegación sea coherente,
la función necesita "recordar" el comando actual donde se quedó
en la última llamada. Es decir, debe mantener la referencia
al nodo del historial (current) entre invocaciones.

Sin static, el valor de current se inicializaría a NULL
en cada llamada, haciendo imposible continuar la navegación
desde donde se quedó.*/