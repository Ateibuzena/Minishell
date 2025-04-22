/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:29:09 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 20:29:27 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"


static char	*extract_file(char *token)
{
	char	*res;

	res = ft_strchr(token, ' ');
	if (!res)
		return (NULL);
	return (ft_strdup(res + 1));
}

t_command	*init_command(void)
{
	t_command *cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->cmd = malloc(sizeof(char *) * 256);
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_executor	*parse_commands(char **argv)
{
	t_executor	*exec;
	t_command	*curr;
	int			i, cmd_idx;

	exec = malloc(sizeof(t_executor));
	if (!exec)
		return (NULL);  // primer malloc crítico
	exec->commands = malloc(sizeof(t_command *) * 256); // max comandos
	if (!exec->commands)
	{
		free(exec);
		return (NULL);  // liberar lo anterior
	}
	exec->count = 0;
	curr = init_command();
	if (!curr)
	{
		free_partial_executor(exec);
		return (NULL);
	}
	cmd_idx = 0;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "|", 1) == 0)
		{
			curr->cmd[cmd_idx] = NULL;
			exec->commands[exec->count++] = curr;
			curr = malloc(sizeof(t_command));
			ft_memset(curr, 0, sizeof(t_command));
			curr->cmd = malloc(sizeof(char *) * 256);
			cmd_idx = 0;
		}
		else if (ft_strncmp(argv[i], "<<", 2) == 0)
		{
			curr->heredoc = extract_file(argv[i]);
		}
		else if (ft_strncmp(argv[i], "<", 1) == 0 && ft_strncmp(argv[i], "<<", 2) != 0)
			curr->infile = extract_file(argv[i]);
		else if (ft_strncmp(argv[i], ">>", 2) == 0 && ft_strncmp(argv[i], ">", 1) != 0)
		{
			curr->outfile = extract_file(argv[i]);
			curr->append = 1;
		}
		else if (ft_strncmp(argv[i], ">", 1) == 0)
		{
			curr->outfile = extract_file(argv[i]);
			curr->append = 0;
		}
		else
		{
			char **split = ft_split(argv[i], ' ');
			for (int k = 0; split[k]; k++)
				curr->cmd[cmd_idx++] = ft_strdup(split[k]);
			ft_freedouble(split);
		}
		i++;
	}
	curr->cmd[cmd_idx] = NULL;
	exec->commands[exec->count++] = curr;
	return (exec);
}
