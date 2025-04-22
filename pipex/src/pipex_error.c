/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:03:22 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 20:21:59 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_perror(const char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_errno(char *argument)
{
	if (errno == ENOENT)
		(ft_perror("pipex: "), ft_perror(argument),
			ft_perror(": No such file or directory\n"));
	else if (errno == EACCES)
		(ft_perror("pipex: "), ft_perror(argument),
			ft_perror(": Permission denied\n"));
	else if (errno == ENOMEM)
		ft_perror("pipex: Out of memory\n");
	else if (errno == EINVAL)
		ft_perror("pipex: Invalid argument\n");
	else if (errno == EISDIR)
		ft_perror("pipex: Is a directory\n");
	else if (errno == EMFILE)
		ft_perror("pipex: Too many open files\n");
	else if (errno == ENFILE)
		ft_perror("pipex: Too many open files in system\n");
	else if (errno == EFAULT)
		ft_perror("pipex: Bad address\n");
	else if (errno == EROFS)
		ft_perror("pipex: Read-only file system\n");
	else if (errno == ETXTBSY)
		ft_perror("pipex: Text file busy\n");
	else
		ft_perror("pipex: Open failed\n");
}
