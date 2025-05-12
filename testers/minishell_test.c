/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:00:00 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/12 21:59:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/minishellft.h"
/*
static void	ft_cleanup_group(char **group_result)
{
	int	i;

	if (!group_result)
		return;
	i = 0;
	while (group_result[i])
	{
		free(group_result[i]);  // ✅ Liberamos cada elemento del array
		i++;
	}
	free(group_result);  // ✅ Liberamos el array en sí
}


// Helper function to simulate input and test memory leaks
void	test_minishell_input(char *input, char **envp)
{
	t_Minishell	shell;

	printf("=== Testing input: '%s' ===\n", input);
	ft_initialize_shell(&shell, envp);
	shell.input = ft_strdup(input);
	if (!ft_process_input(&shell))
	{
		printf("Error processing input: '%s'\n", input);
		ft_cleanup_shell(&shell);
		return ;
	}
	shell.status = ft_handle_pipeline(&shell);
	ft_cleanup_shell(&shell);
	printf("Test completed for input: '%s'\n\n", input);
}

// Test suite for minishell
void	run_minishell_tests(char **envp)
{
	printf("===== MINISHELL TEST SUITE =====\n\n");

	// Test 1: Simple command
	//test_minishell_input("echo Hello, World!", envp);

	// Test 2: Command with pipe
	test_minishell_input("echo Hello | grep H", envp);

	// Test 3: Command with redirection
	//test_minishell_input("echo Hello > testfile", envp);

	// Test 4: Command with multiple pipes
	//test_minishell_input("echo Hello | grep H | wc -l", envp);

	// Test 5: Invalid syntax
	//test_minishell_input("echo Hello | | grep H", envp);

	// Test 6: Builtin command
	//test_minishell_input("export TEST_VAR=value", envp);

	// Test 7: Environment variable expansion
	//test_minishell_input("echo $TEST_VAR", envp);

	// Test 8: Empty input
	//test_minishell_input("", envp);

	// Test 9: Input with only spaces
	//test_minishell_input("   ", envp);

	// Test 10: Complex command
	//test_minishell_input("echo Hello && echo World || echo Error", envp);

	printf("All tests completed successfully!\n");
	printf("If running with Valgrind, check for memory leaks:\n");
	printf("valgrind --leak-check=full --show-leak-kinds=all ./minishell_test");
	printf("\n");
}

// gcc -o minishell_test $(find ../minishell -name "*.c") ./minishell_test.c 
//-I../../parser -I../pipex  -I../tokens -I../prompt -I../builtins 
//-I../enviroment -I../history -I../signals -I../libft ../parser/parser.a 
//../pipex/pipex.a ../tokens/tokens.a ../prompt/prompt.a 
//../builtins/builtins.a ../enviroment/enviroment.a ../history/history.a 
//../signals/signals.a  ../libft/libft.a -lreadline

// Main function to execute the test suite
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	run_minishell_tests(envp);
	return (0);
}
*/