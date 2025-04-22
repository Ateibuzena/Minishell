/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:56:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 21:33:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_pipex(char **argv, t_Env *env, t_History *history)
{
	t_executor	*exec;

	if (!argv || !argv[0])
		return (ft_perror("Pipex error: No input\n"), 1);
	exec = parse_commands(argv);
	execute_pipeline(exec, env, history);
	
	free_executor(exec);
	return (0);
}
