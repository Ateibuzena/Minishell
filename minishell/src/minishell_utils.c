/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:24:07 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 22:27:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

int	ft_redirect_input(char *file, char *heredoc_delim)
{
	int	fd;

	if (!file && !heredoc_delim)
		return (perror("file and heredoc_delim are NULL"), -1);
	if (heredoc_delim)
	{
		fd = ft_here_doc(heredoc_delim);
		if (fd < 0)
			return (-1);
	}
	else
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (perror(file), -1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		return (perror("dup2 input"), close(fd), -1);
	close(fd);
	return (0);
}

int	ft_redirect_output(char *file)
{
	int	fd;

	if (!file)
		return (perror("file is NULL"), -1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(file), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("dup2 output"), close(fd), -1);
	close(fd);
	return (0);
}

int	ft_redirect_append(char *file)
{
	int	fd;

	if (!file)
		return (perror("file is NULL"), -1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(file), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (perror("dup2 append"), close(fd), -1);
	close(fd);
	return (0);
}

void	ft_save_descriptors(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

void	ft_restore_descriptors(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("dup2 (restore stdin)");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("dup2 (restore stdout)");
	if (close(saved_stdin) == -1)
		perror("close (saved_stdin)");
	if (close(saved_stdout) == -1)
		perror("close (saved_stdout)");
}
