/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:56:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/16 21:31:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_pipex(char **input, char **env, t_History *history)
{
	t_pipex	*pipex;
	int		status;

	status = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (ft_perror("Malloc error: pipex\n"), 1);
	ft_memset(pipex, 0, sizeof(t_pipex));
	ft_init(pipex, input, history);
	ft_first_process(pipex, env);
	ft_middle_process(pipex, env);
	ft_last_process(pipex, env);
	status = pipex->status;
	fprintf(stderr, "\nStatus: %d\n", status);
	ft_free_pipex(&pipex);
	return (status);
}
