/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:35:24 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 00:02:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

static int	handle_pipes_with_redirections(char **argv, t_context *ctx,
		t_History *history, t_Env *env)
{
	char	**split;
	int		status;

	if (ft_handle_redirections(argv, &ctx->stdin_backup,
			&ctx->stdout_backup) == -1)
		return (ft_freedouble(argv), 1);
	split = ft_split(argv[ctx->builtin], ' ');
	status = ft_execute_builtins(split, history, &env);
	ft_freedouble(split);
	dup2(ctx->stdin_backup, STDIN_FILENO);
	dup2(ctx->stdout_backup, STDOUT_FILENO);
	close(ctx->stdin_backup);
	close(ctx->stdout_backup);
	return (status);
}

static int	find_builtin_command(char **argv, t_context *ctx)
{
	int		i;
	char	**split;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] && !ft_strchr(argv[i], '|')
			&& !ft_strchr(argv[i], '<') && !ft_strchr(argv[i], '>'))
		{
			split = ft_split(argv[i], ' ');
			if (ft_is_builtins(split[0]))
			{
				ctx->builtin = i;
				ft_freedouble(split);
				return (1);
			}
			ft_freedouble(split);
		}
		i++;
	}
	return (0);
}

static int	process_with_pipe(char **argv, t_History *history, t_Env *env)
{
	int	status;

	fprintf(stderr, "\nPipex con pipes: %s\n", argv[0]);
	status = ft_pipex(argv, env, history);
	return (status);
}

int	ft_handle_pipes(char *input, t_History *history, t_Env *env)
{
	t_context		ctx;
	int				status;

	ctx.status = 0;
	if (!input || !input[0])
		return (ft_perror("Pipex error: NULL input\n"), 1);
	ctx.argv = ft_group_tokens(input);
	if (!ctx.argv || !ctx.argv[0] || !ctx.argv[0][0])
		return (ft_perror("Pipex error: Tokens\n"), 1);
	if (ft_strchr(input, '|'))
		status = process_with_pipe(ctx.argv, history, env);
	else
	{
		if (find_builtin_command(ctx.argv, &ctx))
			status = handle_pipes_with_redirections(ctx.argv,
					&ctx, history, env);
		else
			status = ft_pipex(ctx.argv, env, history);
	}
	ft_freedouble(ctx.argv);
	return (status);
}
