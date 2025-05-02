/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:35:24 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 16:06:57 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

static int	ft_builtin(t_context *ctx, t_Minishell *shell)
{
	char	**split;
	int		status;

	if (ft_handle_redirections(ctx->argv, &ctx->stdin_backup,
			&ctx->stdout_backup) == -1)
		return (ft_freedouble(ctx->argv), 1);
	split = ft_split(ctx->argv[ctx->builtin], ' ');
	status = ft_execute_builtins(split, shell->history, &shell->env);
	ft_freedouble(split);
	dup2(ctx->stdin_backup, STDIN_FILENO);
	dup2(ctx->stdout_backup, STDOUT_FILENO);
	close(ctx->stdin_backup);
	close(ctx->stdout_backup);
	return (status);
}

static int	ft_find_builtin(char **argv, t_context *ctx)
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

int	ft_handle_pipeline(t_Minishell *shell)
{
	t_context	ctx;
	int			status;

	ctx.status = 0;
	if (!shell->cleaned || !shell->cleaned[0])
		return (ft_perror("Pipex error: NULL input\n"), 1);
	ctx.argv = ft_group_tokens(shell->cleaned);
	if (!ctx.argv || !ctx.argv[0] || !ctx.argv[0][0])
		return (ft_perror("Pipex error: Tokens\n"), 1);
	if (ft_strchr(shell->cleaned, '|'))
		status = ft_pipex(ctx.argv, shell->env, shell->history);
	else
	{
		if (ft_find_builtin(ctx.argv, &ctx))
			status = ft_builtin(&ctx, shell);
		else
			status = ft_pipex(ctx.argv, shell->env, shell->history);
	}
	ft_freedouble(ctx.argv);
	return (status);
}
