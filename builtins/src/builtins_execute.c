/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:02:06 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 17:56:25 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

int	ft_execute_builtins(char **args, t_History *history, t_Env **env)
{
	if (ft_strcmp(args[0], "echo"))
		return (ft_echo(args, *env));
	else if (ft_strcmp(args[0], "cd"))
		return (ft_cd(args));
	else if (ft_strcmp(args[0], "clear"))
		return (ft_clear(), 0);
	else if (ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export"))
		return (ft_export(env, args));
	else if (ft_strcmp(args[0], "unset"))
		return (ft_unset(env, args));
	else if (ft_strcmp(args[0], "env"))
		return (ft_env(*env, args));
	else if (ft_strcmp(args[0], "exit"))
		return (ft_exit(args));
	else if (ft_strcmp(args[0], "history"))
		return (ft_show_history(history), 0);
	else
		return (printf("%s: Command not found\n", args[0]));
	return (0);
}

int	ft_is_builtins(char *argv)
{
	char	**args;

	args = ft_split(argv, ' ');
	if (ft_strcmp(args[0], "echo"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "cd"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "clear"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "pwd"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "export"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "unset"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "env"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "exit"))
		return (ft_freedouble(args), 1);
	else if (ft_strcmp(args[0], "history"))
		return (ft_freedouble(args), 1);
	else
		return (ft_freedouble(args), 0);
}
