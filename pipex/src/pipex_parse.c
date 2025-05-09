/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:29:09 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/07 15:24:57 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

static t_command	*ft_new_command(t_command *curr, int *i, t_executor *exec)
{
	curr->cmd[(*i)] = NULL;
	exec->commands[exec->count++] = curr;
	curr = malloc(sizeof(t_command));
	if (!curr)
		return (NULL);
	ft_memset(curr, 0, sizeof(t_command));
	curr->cmd = malloc(sizeof(char *) * 256);
	if (!curr->cmd)
	{
		free(curr);
		return (NULL);
	}
	(*i) = 0;
	return (curr);
}

static char	*ft_extract_file(char *token)
{
	char	*res;
	char	*file;

	res = ft_strchr(token, ' ');
	if (!res)
		return (NULL);
	file = ft_strdup(res + 1);
	return (file);
}

static void	ft_add_args(char *argv, t_command *curr, int *i)
{
	char	**split;
	int		k;

	k = 0;
	split = ft_split(argv, ' ');
	while (split[k])
		curr->cmd[(*i)++] = ft_strdup(split[k++]);
	ft_freedouble(split);
}

static void	ft_process_token(char *token, t_command *curr, int *i)
{
	if (ft_strncmp(token, "<<", 2) == 0)
		curr->heredoc = ft_extract_file(token);
	else if (ft_strncmp(token, "<", 1) == 0)
		curr->infile = ft_extract_file(token);
	else if (ft_strncmp(token, ">>", 2) == 0)
	{
		curr->outfile = ft_extract_file(token);
		curr->append = 1;
	}
	else if (ft_strncmp(token, ">", 1) == 0)
	{
		curr->outfile = ft_extract_file(token);
		curr->append = 0;
	}
	else
		ft_add_args(token, curr, i);
	free(token);
	token = NULL;
}

t_executor	*ft_parse_commands(char **argv)
{
	t_executor	*exec;
	t_command	*curr;
	int			i;
	int			j;

	exec = ft_init_executor();
	curr = ft_init_command();
	if (!curr)
		return (ft_free_executor(exec), NULL);
	i = 0;
	j = 0;
	while (argv[j])
	{
		if (ft_strncmp(argv[j], "|", 1) == 0)
			curr = ft_new_command(curr, &i, exec);
		else
			ft_process_token(argv[j], curr, &i);
		j++;
	}
	curr->cmd[i] = NULL;
	exec->commands[exec->count++] = curr;
	return (exec);
}
