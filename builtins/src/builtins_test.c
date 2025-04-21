/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:42:38 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 21:14:29 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"
/*
int g_last_exit = 27;

// Helper function to print environment list
void	print_env_list(t_Env *env_list)
{
	t_Env	*current;

	current = env_list;
	printf("Environment variables:\n");
	if (!current)
		printf("  (empty list)\n");
	while (current)
	{
		printf("  %s", current->key);
		if (current->value)
			printf("=%s", current->value);
		printf("\n");
		current = current->next;
	}
	printf("\n");
}

// Helper function to setup environment for tests
t_Env	*setup_test_env(void)
{
	t_Env	*env;

	env = NULL;
	ft_add_env(&env, "HOME", "/home/user");
	ft_add_env(&env, "PWD", "/current/path");
	ft_add_env(&env, "OLDPWD", "/previous/path");
	ft_add_env(&env, "PATH", "/usr/bin:/bin");
	ft_add_env(&env, "USER", "azubieta");
	ft_add_env(&env, "TERM", "xterm");
	return (env);
}

// Test echo command
void	test_echo(t_Env *env)
{
	char	*expanded = ft_expand_variables("$USER", env, g_last_exit);
	char	*args1[] = {"echo", "Hello", "World", NULL};
	char	*args2[] = {"echo", "-n", "No", "newline", NULL};
	char	*args3[] = {"echo", "-nnnn", "Multiple", "flags", NULL};
	char	*args4[] = {"echo", "Hello", expanded, "variable", NULL}; // Variable already expanded
	char	*args5[] = {"echo", "-n", NULL};
	char	*args6[] = {"echo", NULL};
	char	*args7[] = {"echo", "-na", "newline", NULL};

	printf("=== Testing echo command ===\n");
	
	printf("Test 1 - Basic echo:\n");
	ft_echo(args1);
	
	printf("\nTest 2 - Echo with no newline:\n");
	ft_echo(args2);
	printf("\n<end of output>\n");
	
	printf("\nTest 3 - Echo with multiple flags:\n");
	ft_echo(args3);
	printf("\n<end of output>\n");
	
	printf("\nTest 4 - Echo with pre-expanded variable $USER:\n");
	ft_echo(args4);
	free(expanded);
	
	printf("\nTest 5 - Echo with just -n flag:\n");
	ft_echo(args5);
	printf("\n<end of output>\n");
	
	printf("\nTest 6 - Echo with no arguments:\n");
	ft_echo(args6);

	printf("\nTest 7 - Echo with invalid flag:\n");
	ft_echo(args7);
	
	printf("\n");
}

// Test pwd command
void	test_pwd(void)
{
	char	cwd_buffer[1024];

	printf("=== Testing pwd command ===\n");
	
	printf("Current working directory from getcwd: %s\n", 
		getcwd(cwd_buffer, sizeof(cwd_buffer)));
	
	printf("Output from ft_pwd:\n");
	ft_pwd();
	
	printf("\n");
}

// Test cd command
void	test_cd(void)
{
	char	*args1[] = {"cd", "..", NULL};
	char	*args2[] = {"cd", NULL};
	char	*args3[] = {"cd", "/tmp", NULL};
	char	*args4[] = {"cd", "-", NULL};
	char	*args5[] = {"cd", "~/Desktop", NULL}; // Tilde expansion
	char	*args6[] = {"cd", "nonexistent_directory", NULL};
	char	*cwd_before[1024];
	char	*cwd_after[1024];

	printf("=== Testing cd command ===\n");
	
	printf("Test 1 - cd to parent directory:\n");
	getcwd((char *)cwd_before, 1024);
	printf("Before: %s\n", (char *)cwd_before);
	ft_cd(args1);
	getcwd((char *)cwd_after, 1024);
	printf("After: %s\n\n", (char *)cwd_after);
	
	printf("Test 2 - cd to home directory:\n");
	getcwd((char *)cwd_before, 1024);
	printf("Before: %s\n", (char *)cwd_before);
	ft_cd(args2);
	getcwd((char *)cwd_after, 1024);
	printf("After: %s\n\n", (char *)cwd_after);
	
	printf("Test 3 - cd to absolute path:\n");
	getcwd((char *)cwd_before, 1024);
	printf("Before: %s\n", (char *)cwd_before);
	ft_cd(args3);
	getcwd((char *)cwd_after, 1024);
	printf("After: %s\n\n", (char *)cwd_after);
	
	printf("Test 4 - cd to previous directory (-):\n");
	getcwd((char *)cwd_before, 1024);
	printf("Before: %s\n", (char *)cwd_before);
	ft_cd(args4);
	getcwd((char *)cwd_after, 1024);
	printf("After: %s\n\n", (char *)cwd_after);
	
	printf("Test 5 - cd with tilde expansion:\n");
	getcwd((char *)cwd_before, 1024);
	printf("Before: %s\n", (char *)cwd_before);
	ft_cd(args5);
	getcwd((char *)cwd_after, 1024);
	printf("After: %s\n\n", (char *)cwd_after);
	
	printf("Test 6 - cd to nonexistent directory:\n");
	getcwd((char *)cwd_before, 1024);
	printf("Before: %s\n", (char *)cwd_before);
	ft_cd(args6);
	getcwd((char *)cwd_after, 1024);
	printf("After: %s\n\n", (char *)cwd_after);
	
	printf("\n");
}

// Test env command
void	test_ft_env(t_Env *env)
{
	char	*args1[] = {"env", NULL};
	char	*args2[] = {"env", "extra_arg", NULL};

	printf("=== Testing env command ===\n");
	
	printf("Test 1 - Basic env command:\n");
	ft_env(env, args1);
	
	printf("\nTest 2 - Env with extra arguments (should show error):\n");
	ft_env(env, args2);
	
	printf("\nTest 3 - Env with NULL environment:\n");
	ft_env(NULL, args1);
	
	printf("\n");
}

// Test export command
void	test_export(t_Env **env)
{
	char	*args1[] = {"export", "NEW_VAR=value", NULL};
	char	*args2[] = {"export", "APPEND_VAR=appended", NULL};
	char	*args3[] = {"export", "EMPTY_VAR=", NULL};
	char	*args4[] = {"export", "123INVALID=test", NULL};
	char	*args5[] = {"export", "MULTI_VAR1=val1", "MULTI_VAR2=val2", NULL};
	char	*args6[] = {"export", NULL};

	printf("=== Testing export command ===\n");
	
	printf("Initial environment:\n");
	print_env_list(*env);
	
	printf("Test 1 - Export new variable:\n");
	ft_export(env, args1);
	print_env_list(*env);
	
	printf("Test 2 - Export variable with same name (should overwrite):\n");
	ft_add_env(env, "APPEND_VAR", "original");
	print_env_list(*env);
	ft_export(env, args2);
	print_env_list(*env);
	
	printf("Test 3 - Export variable with empty value:\n");
	ft_export(env, args3);
	print_env_list(*env);
	
	printf("Test 4 - Export invalid variable name (should fail):\n");
	ft_export(env, args4);
	print_env_list(*env);
	
	printf("Test 5 - Export multiple variables:\n");
	ft_export(env, args5);
	print_env_list(*env);
	
	printf("Test 6 - Export with no arguments:\n");
	ft_export(env, args6);
	print_env_list(*env);
	
	printf("\n");
}

// Test unset command
void	test_unset(t_Env **env)
{
	char	*args1[] = {"unset", "USER", NULL};
	char	*args2[] = {"unset", "NONEXISTENT", NULL};
	char	*args3[] = {"unset", "PATH", "TERM", NULL};
	char	*args4[] = {"unset", "123INVALID", NULL};
	char	*args5[] = {"unset", NULL};

	printf("=== Testing unset command ===\n");
	
	printf("Initial environment:\n");
	print_env_list(*env);
	
	printf("Test 1 - Unset existing variable:\n");
	ft_unset(env, args1);
	print_env_list(*env);
	
	printf("Test 2 - Unset non-existent variable:\n");
	ft_unset(env, args2);
	print_env_list(*env);
	
	printf("Test 3 - Unset multiple variables:\n");
	ft_unset(env, args3);
	print_env_list(*env);
	
	printf("Test 4 - Unset with invalid name:\n");
	ft_unset(env, args4);
	print_env_list(*env);
	
	printf("Test 5 - Unset with no arguments:\n");
	ft_unset(env, args5);
	print_env_list(*env);
	
	printf("\n");
}


// Test variable expansion
void	test_variable_expansion(t_Env *env)
{
	printf("=== Testing variable expansion ===\n");
	
	printf("Test 1 - Expand existing variable:\n");
	printf("$USER expands to: %s\n", ft_expand_variables("$HOME", env, g_last_exit));
	
	printf("Test 2 - Expand non-existent variable:\n");
	printf("$NONEXISTENT expands to: %s\n", 
		ft_expand_variables("$NONEXISTENT", env, g_last_exit));
	
	printf("Test 3 - Regular string (no expansion):\n");
	printf("'Regular string' expands to: %s\n", 
		ft_expand_variables("Regular string", env, g_last_exit));
	
	printf("Test 4 - NULL input:\n");
	printf("NULL expands to: %s\n", ft_expand_variables(NULL, env, g_last_exit));
	
	printf("Test 5 - Expand last exit code ($?):\n");
	printf("$? expands to: %s\n", ft_expand_variables("$?", env, g_last_exit));
	
	printf("Test 6 - Expand inside double quotes:\n");
	printf("\"$HOME\" expands to: %s\n", ft_expand_variables("\"$HOME\"", env, g_last_exit));
	
	printf("Test 7 - Ignore expansion inside single quotes:\n");
	printf("'$HOME' expands to: %s\n", ft_expand_variables("'$HOME'", env, g_last_exit));
	
	printf("Test 8 - Mixed content:\n");
	printf("Hello \"$HOME\" World expands to: %s\n", 
		ft_expand_variables("Hello \"$HOME\" World", env, g_last_exit));
	
	printf("\n");
}

// Test tilde expansion
void	test_tilde_expansion(void)
{
	char	*expanded;

	printf("=== Testing tilde expansion ===\n");
	
	expanded = ft_expand_tilde("~");
	printf("Test 1 - '~' expands to: %s\n", expanded);
	free(expanded);
	
	expanded = ft_expand_tilde("~/Documents");
	printf("Test 2 - '~/Documents' expands to: %s\n", expanded);
	free(expanded);
	
	expanded = ft_expand_tilde("/usr/bin");
	printf("Test 3 - '/usr/bin' (no tilde) expands to: %s\n", expanded);
	free(expanded);
	
	expanded = ft_expand_tilde("~user/path");
	printf("Test 4 - '~user/path' expands to: %s\n", expanded);
	free(expanded);
	
	expanded = ft_expand_tilde(NULL);
	printf("Test 5 - NULL input handled as: %s\n", 
		expanded ? expanded : "(null)");
	free(expanded);
	
	printf("\n");
}

// Test is_builtins function
void	test_is_builtins(void)
{
	printf("=== Testing is_builtins function ===\n");
	
	printf("'echo test': %s\n", ft_is_builtins("echo test") ? "TRUE" : "FALSE");
	printf("'cd /tmp': %s\n", ft_is_builtins("cd /tmp") ? "TRUE" : "FALSE");
	printf("'pwd': %s\n", ft_is_builtins("pwd") ? "TRUE" : "FALSE");
	printf("'export VAR=val': %s\n", 
		ft_is_builtins("export VAR=val") ? "TRUE" : "FALSE");
	printf("'unset PATH': %s\n",
		ft_is_builtins("unset PATH") ? "TRUE" : "FALSE");
	printf("'env': %s\n", ft_is_builtins("env") ? "TRUE" : "FALSE");
	printf("'exit 0': %s\n", ft_is_builtins("exit 0") ? "TRUE" : "FALSE");
	printf("'ls -la': %s\n", ft_is_builtins("ls -la") ? "TRUE" : "FALSE");
	printf("'grep pattern': %s\n", 
		ft_is_builtins("grep pattern") ? "TRUE" : "FALSE");
	
	printf("\n");
}

// Test strtok function
void	test_strtok(void)
{
	char	str1[] = "export VAR=value";
	char	str2[] = "echo Hello World";
	char	str3[] = "cd /path/to/dir";
	char	str4[] = "one:two:three:four";
	char	*token;

	printf("=== Testing ft_strtok function ===\n");
	
	printf("Test 1 - Space delimiter:\n");
	token = ft_strtok(str1, " ");
	while (token)
	{
		printf("Token: '%s'\n", token);
		token = ft_strtok(NULL, " ");
	}
	
	printf("\nTest 2 - Multiple spaces:\n");
	token = ft_strtok(str2, " ");
	while (token)
	{
		printf("Token: '%s'\n", token);
		token = ft_strtok(NULL, " ");
	}
	
	printf("\nTest 3 - Path with slashes:\n");
	token = ft_strtok(str3, "/");
	while (token)
	{
		printf("Token: '%s'\n", token);
		token = ft_strtok(NULL, "/");
	}
	
	printf("\nTest 4 - Colon separator:\n");
	token = ft_strtok(str4, ":");
	while (token)
	{
		printf("Token: '%s'\n", token);
		token = ft_strtok(NULL, ":");
	}
	
	printf("\n");
}

// Mock history for testing
void	create_test_history(t_History *history)
{
	// Add some test commands to the history
	ft_add_entry(history, "echo first command");
	ft_add_entry(history, "cd /tmp");
	ft_add_entry(history, "pwd");
	ft_add_entry(history, "export TEST=value");
	ft_add_entry(history, "env");

}

// Test execute_builtins
void	test_execute_builtins(t_Env **env)
{
	t_History	*history;
	char		*args1[] = {"echo", "echo", "execute", NULL};
	char		*args2[] = {"pwd", NULL};
	char		*args3[] = {"env", NULL};
	char		*args4[] = {"history", NULL};
	char		*args5[] = {"invalid_command", NULL};

	history = (t_History *)malloc(sizeof(t_History));
    if (!history)
    	perror("Malloc error: History\n");
    ft_init_history(history);
	create_test_history(history);
	
	printf("=== Testing ft_execute_builtins ===\n");
	
	printf("Test 1 - Execute echo:\n");
	ft_execute_builtins(args1, history, env);
	
	printf("\nTest 2 - Execute pwd:\n");
	ft_execute_builtins(args2, history, env);
	
	printf("\nTest 3 - Execute env:\n");
	ft_execute_builtins(args3, history, env);
	
	printf("\nTest 4 - Execute history:\n");
	ft_execute_builtins(args4, history, env);
	
	printf("\nTest 5 - Execute invalid command:\n");
	ft_execute_builtins(args5, history, env);
	
	// Clean up history
	ft_free_history(history);
	
	printf("\n");
}

// gcc -o builtins_test $(find . -name "*.c") -I../../history -I../../enviroment -I../../libft ../../history/history.a ../../enviroment/enviroment.a ../../libft/libft.a -lreadline

int	main(void)
{
	t_Env	*test_env;

	printf("===== BUILTINS FUNCTIONS TEST SUITE =====\n\n");

	test_env = setup_test_env();

	test_echo(test_env);
	test_pwd();
	test_cd();
	test_ft_env(test_env);
	test_export(&test_env);
	test_unset(&test_env);
	test_variable_expansion(test_env);
	test_tilde_expansion();
	test_is_builtins();
	test_strtok();
	test_execute_builtins(&test_env);
	
	// Clean up
	ft_free_env(test_env);
	
	printf("All tests completed successfully!\n");
	printf("If running with Valgrind, check for memory leaks.\n");
	return (0);
}
*/