/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:55:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 22:32:26 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

static char	*get_redirection_target(char *arg)
{
	char	*res;

	while (*arg == ' ' || *arg == '\t')
		arg++;
	res = ft_strtrim(arg, " \t");
	return (res);
}

static int	ft_handle_redirection_type(char *arg, int *i)
{
	if (!arg || !*arg)
		return (-1);
	if (ft_strncmp(arg, "<<", 2) == 0)
		return (handle_heredoc(arg, i));
	else if (ft_strncmp(arg, "<", 1) == 0)
		return (handle_input_redir(arg));
	else if (ft_strncmp(arg, ">>", 2) == 0)
		return (handle_append_redir(arg));
	else if (ft_strncmp(arg, ">", 1) == 0)
		return (handle_output_redir(arg));
	return (0);
}

int	ft_handle_redirections(char **argv, int *stdin, int *stdout)
{
	int	i;

	i = 0;
	if (!argv || !argv[0])
		return (-1);
	ft_save_descriptors(stdin, stdout);
	while (argv[i])
	{
		if (ft_handle_redirection_type(argv[i], &i) < 0)
			return (-1);
		i++;
	}
	return (0);
}
