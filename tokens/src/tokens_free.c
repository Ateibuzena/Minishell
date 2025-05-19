/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:37:38 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/18 23:58:57 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

void	ft_free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->result)
	{
		ft_freedouble(token->result);
		token->result = NULL;
	}
	free(token);
	token = NULL;
}

void	ft_free_group(t_group *group)
{
	if (!group)
		return ;
	if (group->input)
	{
		ft_freedouble(group->input);
		group->input = NULL;
	}
	if (group->result)
	{
		ft_freedouble(group->result);
		group->result = NULL;
	}
	free(group);
	group = NULL;
}

void	ft_remove_pipes(char **result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (result[i])
	{
		if (ft_strcmp(result[i], "|") == 0)
		{
			result[j] = result[i];
			j++;
		}
		else
		{
			free(result[i]);
			result[i] = NULL;
		}
		i++;
	}
	result[j] = NULL;
}
