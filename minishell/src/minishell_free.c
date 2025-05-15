/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:27:12 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/14 19:36:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

static void	ft_shellclean_strings(t_Minishell **shell)
{
	if ((*shell)->input)
	{
		free((*shell)->input);
		(*shell)->input = NULL;
	}
	if ((*shell)->cleaned)
	{
		free((*shell)->cleaned);
		(*shell)->cleaned = NULL;
	}
	if ((*shell)->expanded)
	{
		free((*shell)->expanded);
		(*shell)->expanded = NULL;
	}
	if ((*shell)->normalized)
	{
		free((*shell)->normalized);
		(*shell)->normalized = NULL;
	}
	if ((*shell)->prompt)
	{
		free((*shell)->prompt);
		(*shell)->prompt = NULL;
	}
}

static void	ft_shellclean_structures(t_Minishell **shell)
{
	if ((*shell)->history)
	{
		ft_free_history((*shell)->history);
		(*shell)->history = NULL;
	}
	if ((*shell)->env)
	{
		printf("freeing env\n");
		ft_free_env((*shell)->env);
		(*shell)->env = NULL;
	}
}

void	ft_cleanup_shell(t_Minishell *shell)
{
	ft_shellclean_strings(&shell);
	ft_shellclean_structures(&shell);
}
