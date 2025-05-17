/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:54:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/17 19:13:39 by azubieta         ###   ########.fr       */
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
			ft_free_pipex(pipex);
			exit(EXIT_FAILURE);
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
			ft_free_pipex(pipex);
			exit(EXIT_FAILURE);
		}
	}
	return (outfile);
}

void	ft_handle_dup2(t_pipex *pipex, int infile, int outfile)
{
	if (infile != -1)
	{
		if (dup2(infile, STDIN_FILENO) < 0)
			(ft_perror("dup2 in\n"), ft_free_pipex(pipex), exit(EXIT_FAILURE));
		close(infile);
	}
	else if (pipex->prev_fd != -1)
	{
		if (dup2(pipex->prev_fd, STDIN_FILENO) < 0)
			(ft_perror("dup2 prev_fd\n"), ft_free_pipex(pipex), exit(EXIT_FAILURE));
		close(pipex->prev_fd);
	}
	if (outfile != -1)
	{
		if (dup2(outfile, STDOUT_FILENO) < 0)
			(ft_perror("dup2 out\n"), ft_free_pipex(pipex), exit(EXIT_FAILURE));
		close(outfile);
	}
	else if (pipex->fd[1] != -1)
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) < 0)
			(ft_perror("dup2 pipe out\n"), ft_free_pipex(pipex), exit(EXIT_FAILURE));
		close(pipex->fd[1]);
	}
}
