/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:37:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/14 19:42:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

void	ft_initialize_shell(t_Minishell *shell, char **envp)
{
	shell->status = 0;
	shell->prompt = NULL;
	shell->input = NULL;
	shell->normalized = NULL;
	shell->expanded = NULL;
	shell->cleaned = NULL;
	ft_setup_signals();
	shell->env = ft_copy_env(envp);
	if (!shell->env)
		(ft_perror("Malloc error: Env\n"), exit(EXIT_FAILURE));
	shell->history = (t_History *)malloc(sizeof(t_History));
	if (!shell->history)
		(ft_perror("Malloc error: History\n"),
			ft_free_env(shell->env), exit(EXIT_FAILURE));
	ft_init_history(shell->history);
}

int	ft_read_input(t_Minishell *shell)
{
	shell->prompt = ft_prompt(shell->env);
	if (!shell->prompt)
		return (ft_perror("minishell error: prompt\n"), 0);
	*get_g_in_readline() = 1;
	shell->input = readline(shell->prompt);
	*get_g_in_readline() = 0;
	free(shell->prompt);
	shell->prompt = NULL;
	if (!shell->input)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (shell->input[0] == '\0')
	{
		free(shell->input);
		shell->input = NULL;
		return (1);
	}
	return (2);
}

int	ft_process_input(t_Minishell *shell)
{
	shell->normalized = ft_normalize_input(shell->input);
	free(shell->input);
	shell->input = NULL;
	if (!shell->normalized)
		return (ft_perror("minishell error: normalize\n"), 0);
	if (!validate_syntax(shell->normalized))
	{
		(ft_perror("minishell: syntax error\n"), free(shell->normalized));
		shell->normalized = NULL;
		return (0);
	}
	shell->expanded = ft_expand_variables(shell->normalized,
			shell->env, shell->status);
	free(shell->normalized);
	shell->normalized = NULL;
	if (!shell->expanded)
		return (ft_perror("minishell error: expand\n"), 0);
	shell->cleaned = ft_handle_quotes(shell->expanded);
	free(shell->expanded);
	shell->expanded = NULL;
	if (!shell->cleaned)
		return (ft_perror("minishell error: handle_quotes\n"), 0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_Minishell	shell;
	int			result;

	(void)argv;
	if (argc > 1)
		return (ft_perror("minishell error: arguments\n"), 1);
	ft_initialize_shell(&shell, envp);
	while (1)
	{
		if (g_exit || g_exit == -1)
			break ;
		result = ft_read_input(&shell);
		if (result == 0)
			break ;
		if (result == 1)
			continue ;
		ft_add_entry(shell.history, shell.input);
		if (!ft_process_input(&shell))
		{
			free(shell.cleaned);
			continue ;
		}
		shell.status = ft_handle_pipeline(&shell);
		printf("freeing env\n");
	}
	return (ft_cleanup_shell(&shell), 0);
}
