/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historyft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:40:23 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/29 20:24:04 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_HistoryEntry
{
	char				*line;
	struct s_HistoryEntry	*next;
}	t_HistoryEntry;

typedef struct s_History
{
	t_HistoryEntry	*head;
	t_HistoryEntry	*tail;
	int				size;
}	t_History;

/*history_init.c*/
t_HistoryEntry	*ft_new_entry(const char *line);
void			ft_init_history(t_History	*history);

/*history_utils.c*/
void			ft_add_entry(t_History *history, const char *line);
void			ft_show_history(t_History *history);
char			*ft_navigate_history(t_History *history, int *index, int key);

/*history_free.c*/
void			ft_free_history(t_History *history);

#endif