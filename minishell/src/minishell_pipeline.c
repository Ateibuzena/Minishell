/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:35:24 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/22 17:07:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

static int	ft_builtin(t_context *ctx, t_Minishell *shell)
{
	char	**split;
	int		status;

	if (ft_handle_redirections(ctx->argv, &ctx->stdin_backup,
			&ctx->stdout_backup) == -1)
		return (1);
	split = ft_split(ctx->argv[ctx->builtin], ' ');
	if (!split)
		return (ft_perror("Pipex error: NULL split\n"), 1);
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

void	ft_execute_pipeline(t_Minishell **shell, t_context *ctx)
{
	char	*temp;

	temp = ft_strchr((*shell)->cleaned, '|');
	if (temp)
	{
		free((*shell)->cleaned);
		(*shell)->cleaned = NULL;
		ctx->exit = ft_pipex(ctx->argv, &(*shell)->env, (*shell)->history);
	}
	else
	{
		free((*shell)->cleaned);
		(*shell)->cleaned = NULL;
		if (ft_find_builtin(ctx->argv, ctx))
		{
			ctx->exit = ft_builtin(ctx, (*shell));
			ft_freedouble(ctx->argv);
		}
		else
			ctx->exit = ft_pipex(ctx->argv, &(*shell)->env, (*shell)->history);
	}
}

int	ft_handle_pipeline(t_Minishell *shell)
{
	t_context	ctx;

	if (!shell->cleaned || !shell->cleaned[0])
		return (ft_perror("Pipex error: NULL input\n"), 1);
	ctx.exit = 0;
	ctx.input = ft_split_command(shell->cleaned);
	ctx.len = ft_strlen_double(ctx.input);
	ctx.argv = ft_group_tokens(ctx.input, ctx.len);
	if (!ctx.argv)
		return (ft_perror("Pipex error: NULL argv\n"), 1);
	if (!ctx.argv[0] || !ctx.argv[0][0])
		return (ft_perror("Pipex error: Tokens\n"), ft_freedouble(ctx.argv), 1);
	ft_execute_pipeline(&shell, &ctx);
	return (ctx.exit);
}
