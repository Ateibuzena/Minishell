/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:32:03 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 22:37:06 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

int	handle_heredoc(char *arg, int *i)
{
	char	*filename;

	filename = get_redirection_target(arg + 2);
	if (!filename || ft_redirect_input(filename, filename) < 0)
		return (free(filename), -1);
	(*i)++;
	free(filename);
	return (0);
}

int	handle_input_redir(char *arg)
{
	char	*filename;

	filename = get_redirection_target(arg + 1);
	if (!filename || ft_redirect_input(filename, NULL) < 0)
		return (free(filename), -1);
	free(filename);
	return (0);
}

int	handle_append_redir(char *arg)
{
	char	*filename;

	filename = get_redirection_target(arg + 2);
	if (!filename || ft_redirect_append(filename) < 0)
		return (free(filename), -1);
	free(filename);
	return (0);
}

int	handle_output_redir(char *arg)
{
	char	*filename;

	filename = get_redirection_target(arg + 1);
	if (!filename || ft_redirect_output(filename) < 0)
		return (free(filename), -1);
	free(filename);
	return (0);
}
