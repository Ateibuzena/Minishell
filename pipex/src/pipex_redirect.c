/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:54:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/30 17:04:55 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_handle_input(t_pipex *pipex)
{
	int			infile;
	t_command	*cmd;

	infile = -1;
	cmd = pipex->exec->commands[pipex->i];
	if (cmd->infile || cmd->heredoc)
	{
		if (cmd->heredoc)
			infile = ft_here_doc(cmd->heredoc);
		else
			infile = open(cmd->infile, O_RDONLY);
		if (infile < 0)
		{
			ft_errno(cmd->infile);
			exit(1);
		}
	}
	return (infile);
}

int	ft_handle_output(t_pipex *pipex)
{
	int			outfile;
	int			flags;
	t_command	*cmd;

	outfile = -1;
	cmd = pipex->exec->commands[pipex->i];
	if (cmd->outfile)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		outfile = open(cmd->outfile, flags, 0644);
		if (outfile < 0)
		{
			ft_errno(cmd->outfile);
			exit(1);
		}
	}
	return (outfile);
}

void	ft_handle_dup2(t_pipex *pipex, int infile, int outfile)
{
	if (infile != -1)
	{
		if (dup2(infile, STDIN_FILENO) < 0)
			(ft_perror("dup2 in\n"), exit(1));
		close(infile);
	}
	else if (pipex->prev_fd != -1)
	{
		if (dup2(pipex->prev_fd, STDIN_FILENO) < 0)
			(ft_perror("dup2 prev_fd\n"), exit(1));
		close(pipex->prev_fd);
	}
	if (outfile != -1)
	{
		if (dup2(outfile, STDOUT_FILENO) < 0)
			(ft_perror("dup2 out\n"), exit(1));
		close(outfile);
	}
	else if (pipex->fd[1] != -1)
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) < 0)
			(ft_perror("dup2 pipe out\n"), exit(1));
		close(pipex->fd[1]);
	}
}
