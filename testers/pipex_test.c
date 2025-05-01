/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:08:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 16:14:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipexft.h"
/*
// Helper function to print commands in executor
void	print_executor(t_executor *exec)
{
	int i, j;

	printf("Executor contains %d commands:\n", exec->count);
	for (i = 0; i < exec->count; i++)
	{
		printf("Command %d:\n", i + 1);
		printf("  Infile: %s\n",
			exec->commands[i]->infile ? exec->commands[i]->infile : "(null)");
		printf("  Outfile: %s\n",
			exec->commands[i]->outfile ? exec->commands[i]->outfile : "(null)");
		printf("  Heredoc: %s\n",
			exec->commands[i]->heredoc ? exec->commands[i]->heredoc : "(null)");
		printf("  Append: %d\n", exec->commands[i]->append);
		printf("  Args: ");
		for (j = 0; exec->commands[i]->cmd[j]; j++)
			printf("%s ", exec->commands[i]->cmd[j]);
		printf("\n");
	}
}

// Test ft_init_command
void	test_ft_init_command()
{
	printf("=== Testing ft_init_command ===\n");
	t_command *cmd = ft_init_command();
	if (!cmd)
		printf("ft_init_command: Failed to allocate memory\n");
	else
		printf("ft_init_command: Success\n");
	ft_free_command(cmd);
	printf("\n");
}

// Test ft_init_executor
void	test_ft_init_executor()
{
	printf("=== Testing ft_init_executor ===\n");
	t_executor *exec = ft_init_executor();
	if (!exec)
		printf("ft_init_executor: Failed to allocate memory\n");
	else
		printf("ft_init_executor: Success\n");
	ft_free_executor(exec);
	printf("\n");
}

// Test ft_parse_commands
void	test_ft_parse_commands()
{
	printf("=== Testing ft_parse_commands ===\n");
	char *argv[] = {"ls", "|", "grep", "pipex", ">", "output.txt", NULL};
	t_executor *exec = ft_parse_commands(argv);
	if (!exec)
		printf("ft_parse_commands: Failed to parse commands\n");
	else
	{
		printf("ft_parse_commands: Success\n");
		print_executor(exec);
	}
	ft_free_executor(exec);
	printf("\n");
}

// Test ft_envtoarray
void	test_ft_envtoarray()
{
	printf("=== Testing ft_envtoarray ===\n");
	t_Env env1 = {"PATH", "/usr/bin", NULL};
	t_Env env2 = {"HOME", "/home/user", &env1};
	char **env_array = ft_envtoarray(&env2);
	if (!env_array)
		printf("ft_envtoarray: Failed to convert environment to array\n");
	else
	{
		printf("ft_envtoarray: Success\n");
		for (int i = 0; env_array[i]; i++)
			printf("  %s\n", env_array[i]);
	}
	ft_freedouble(env_array);
	printf("\n");
}

// Test ft_here_doc
void	test_ft_here_doc()
{
	char *test_input = malloc(4 * sizeof(char));
	test_input[0] = 'E';
	test_input[1] = 'N';
	test_input[2] = 'D';
	test_input[3] = '\0';
	printf("=== Testing ft_here_doc ===\n");
	int fd = ft_here_doc(test_input);
	free(test_input);
	if (fd < 0)
		printf("ft_here_doc: Failed to create heredoc\n");
	else
	{
		printf("ft_here_doc: Success\n");
		close(fd);
	}
	printf("\n");
}

// Test ft_pipex
void	test_ft_pipex()
{
	printf("=== Testing ft_pipex ===\n");
	char *argv[] = {"ls", "|", "grep", "pipex", NULL};
	t_Env env1 = {"PATH", "/usr/bin", NULL};
	t_History history = {NULL};
	int status = ft_pipex(argv, &env1, &history);
	printf("ft_pipex: Exit status = %d\n", status);
	printf("\n");
}

//gcc -o pipex_test $(find ../pipex -name "*.c") ./pipex_test.c 
//-I../builtins -I../history -I../enviroment -I../libft 
//../builtins/builtins.a ../history/history.a ../enviroment/enviroment.a 
//../libft/libft.a -lreadline

// Main function to run all tests
int	main()
{
	printf("===== PIPEX FUNCTIONS TEST SUITE =====\n\n");

	test_ft_init_command();
	test_ft_init_executor();
	test_ft_parse_commands();
	test_ft_envtoarray();
	test_ft_here_doc();
	test_ft_pipex();

	printf("All tests completed successfully!\n");
	printf("If running with Valgrind, check for memory leaks.\n");
	printf("valgrind --leak-check=full --show-leak-kinds=all
		--track-origins=yes ./pipex_test\n");
	return 0;
}*/
