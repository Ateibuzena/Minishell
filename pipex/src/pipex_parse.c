/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:29:09 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 19:18:46 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

static char	*ft_extract_file(char *str, char *token)
{
	char	*res;
	char	*file;

	if (str)
		free(str);
	res = ft_strchr(token, ' ');
	if (!res || !*(res + 1))
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
		curr->heredoc = ft_extract_file(curr->heredoc, token);
	else if (ft_strncmp(token, "<", 1) == 0)
		curr->infile = ft_extract_file(curr->infile, token);
	else if (ft_strncmp(token, ">>", 2) == 0)
	{
		curr->outfile = ft_extract_file(curr->outfile, token);
		curr->append = 1;
	}
	else if (ft_strncmp(token, ">", 1) == 0)
	{
		curr->outfile = ft_extract_file(curr->outfile, token);
		curr->append = 0;
	}
	else
		ft_add_args(token, curr, i);
}

static t_executor	*ft_init_parser(char **argv, t_par *par)
{
	t_executor	*exec;
	int			len;

	par->i = 0;
	par->j = 0;
	if (!argv || !argv[0])
		return (NULL);
	len = ft_strlen_double(argv);
	exec = ft_init_executor(len);
	return (exec);
}

t_executor	*ft_parse_commands(char **argv)
{
	t_executor	*exec;
	t_par		par;

	exec = ft_init_parser(argv, &par);
	if (!exec)
		return (NULL);
	while (argv[par.j])
	{
		if (ft_strncmp(argv[par.j], "|", 1) == 0)
		{
			exec->commands[exec->count]->cmd[par.i] = NULL;
			exec->count++;
			par.i = 0;
		}
		else
			ft_process_token(argv[par.j], exec->commands[exec->count], &par.i);
		par.j++;
	}
	ft_freedouble(argv);
	exec->commands[exec->count]->cmd[par.i] = NULL;
	exec->count++;
	return (exec);
}
