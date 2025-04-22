/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:00:52 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 20:12:59 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt/promptft.h"
/*
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
	ft_add_env(&env, "HOME", "/home/azubieta");
	ft_add_env(&env, "USER", "azubieta");
	ft_add_env(&env, "PWD", "/home/azubieta/Desktop");
	char	*part1;
	char	*part2;
	char	*session;

	part1 = ft_strjoin("local/ubuntu2204-64:@/tmp/.ICE-unix/1234,", 
					"unix/ubuntu2204-64:/tmp/.ICE-unix/1234.");
	part2 = ft_strjoin(part1, "42malaga.com");
	free(part1);
	session = part2;

	ft_add_env(&env, "SESSION_MANAGER", session);
	free(session);
	ft_add_env(&env, "PATH", "/usr/bin:/bin");
	return (env);
}

// Test ft_find_session and ft_extract_session
void	test_session_functions(void)
{
	t_Env	*env;
	char	*session;
	char	*found;

	printf("=== Testing session functions ===\n");
	
	env = setup_test_env();
	
	printf("Testing ft_find_session:\n");
	found = ft_find_session(env->next->next->next->value); // SESSION_MANAGER
	if (found)
		printf("  Found session in string: %s\n", found);
	else
		printf("  No session found\n");
	
	printf("Testing with local/ prefix:\n");
	found = ft_find_session("local/ubuntu-session");
	if (found)
		printf("  Found session: %s\n", found);
	else
		printf("  No session found\n");
	
	printf("Testing with unix/ prefix:\n");
	found = ft_find_session("unix/ubuntu-session");
	if (found)
		printf("  Found session: %s\n", found);
	else
		printf("  No session found\n");
	
	printf("Testing with no matching prefix:\n");
	found = ft_find_session("test/session");
	if (found)
		printf("  Found session: %s\n", found);
	else
		printf("  No session found\n");
	
	printf("Testing ft_extract_session:\n");
	session = ft_extract_session(env);
	if (session)
	{
		printf("  Extracted session: %s\n", session);
		free(session);
	}
	else
		printf("  No session extracted\n");
	
	printf("Testing with NULL env:\n");
	session = ft_extract_session(NULL);
	if (session)
	{
		printf("  Extracted session: %s\n", session);
		free(session);
	}
	else
		printf("  No session extracted (expected for NULL)\n");
	
	ft_free_env(env);
	printf("\n");
}

// Test ft_find_user and ft_extract_user
void	test_user_functions(void)
{
	t_Env	*env;
	char	*user;

	printf("=== Testing user functions ===\n");
	
	env = setup_test_env();
	
	printf("Testing ft_find_user:\n");
	user = ft_find_user(env);
	if (user)
		printf("  Found user: %s\n", user);
	else
		printf("  No user found\n");
	
	printf("Testing ft_extract_user:\n");
	user = ft_extract_user(env);
	if (user)
	{
		printf("  Extracted user: %s\n", user);
		free(user);
	}
	else
		printf("  No user extracted\n");
	
	printf("Testing with NULL env:\n");
	user = ft_extract_user(NULL);
	if (user)
	{
		printf("  Extracted user: %s\n", user);
		free(user);
	}
	else
		printf("  No user extracted (expected for NULL)\n");
	
	// Test with env without USER
	ft_free_env(env);

	env = NULL;
	ft_add_env(&env, "HOME", "/home/azubieta");

	printf("Testing with env without USER var:\n");
	user = ft_extract_user(env);
	if (user)
	{
		printf("  Extracted user: %s\n", user);
		free(user);
	}
	else
		printf("  No user extracted (expected for missing USER)\n");
		
	ft_free_env(env);

	printf("\n");
}

// Test ft_simplify_path
void	test_simplify_path(void)
{
	char	*result;
	char	*home;
	
	printf("=== Testing ft_simplify_path ===\n");
	
	// First, store the original HOME value
	home = getenv("HOME");
	
	printf("Testing with path equal to HOME:\n");
	result = ft_simplify_path(home);
	if (result)
	{
		printf("  Simplified path: %s\n", result);
		free(result);
	}
	else
		printf("  No path returned\n");
	
	printf("Testing with path under HOME:\n");
	if (home)
	{
		char	full_path[1024];
		
		snprintf(full_path, sizeof(full_path), "%s/Documents", home);
		result = ft_simplify_path(full_path);
		if (result)
		{
			printf("  Original: %s\n", full_path);
			printf("  Simplified: %s\n", result);
			free(result);
		}
		else
			printf("  No path returned\n");
	}
	
	printf("Testing with path not under HOME:\n");
	result = ft_simplify_path("/usr/local/bin");
	if (result)
	{
		printf("  Simplified path: %s\n", result);
		free(result);
	}
	else
		printf("  No path returned\n");
	
	printf("Testing with NULL input:\n");
	result = ft_simplify_path(NULL);
	if (result)
	{
		printf("  Result: %s\n", result);
		free(result);
	}
	else
		printf("  NULL returned (expected)\n");
	
	printf("\n");
}

// Test ft_build_prompt
void	test_build_prompt(void)
{
	char	prompt[1024];
	char	*user;
	char	*session;
	char	*path;
	
	printf("=== Testing ft_build_prompt ===\n");
	
	printf("Testing normal prompt building:\n");
	user = ft_strdup("azubieta");
	session = ft_strdup("ubuntu");
	path = ft_strdup("~/Desktop");
	
	ft_build_prompt(prompt, user, session, path);
	printf("  Built prompt: '%s'\n", prompt);
	
	printf("Testing with different values:\n");
	user = ft_strdup("guest");
	session = ft_strdup("remote");
	path = ft_strdup("/tmp");
	
	ft_build_prompt(prompt, user, session, path);
	printf("  Built prompt: '%s'\n", prompt);
	
	printf("\n");
}

// Test ft_prompt with full env
void	test_prompt(void)
{
	t_Env	*env;
	char	*prompt;
	
	printf("=== Testing ft_prompt ===\n");
	
	env = setup_test_env();
	
	printf("Testing with valid environment:\n");
	prompt = ft_prompt(env);
	if (prompt)
	{
		printf("  Generated prompt: '%s'\n", prompt);
		free(prompt);
	}
	else
		printf("  No prompt generated\n");
	
	printf("Testing with NULL environment:\n");
	prompt = ft_prompt(NULL);
	if (prompt)
	{
		printf("  Generated prompt: '%s'\n", prompt);
		free(prompt);
	}
	else
		printf("  No prompt generated (expected for NULL)\n");
	
	ft_free_env(env);
	printf("\n");
}

// Test all edge cases
void	test_edge_cases(void)
{
	t_Env	*env;
	char	*session;
	char	*user;
	char	*path;
	char	*prompt;
	
	printf("=== Testing edge cases ===\n");
	env = NULL;
	ft_add_env(&env, "USER", NULL); // User with NULL value
	ft_add_env(&env, "SESSION_MANAGER", NULL); // Session with NULL value
	
	printf("Testing extraction with NULL values:\n");
	user = ft_extract_user(env);
	printf("  User extraction: %s\n", user ? user : "(NULL)");
	free(user);
	
	session = ft_extract_session(env);
	printf("  Session extraction: %s\n", session ? session : "(NULL)");
	free(session);
	
	printf("Testing path simplification with empty string:\n");
	path = ft_simplify_path("");
	printf("  Path simplification: %s\n", path ? path : "(NULL)");
	free(path);
	
	printf("Testing prompt with minimal env:\n");
	prompt = ft_prompt(env);
	printf("  Prompt generation: %s\n", prompt ? prompt : "(NULL)");
	free(prompt);
	
	ft_free_env(env);
	printf("\n");
}

// gcc -o prompt_test $(find ../prompt -name "*.c") ./prompt_test.c -I../enviroment -I../libft ../enviroment/enviroment.a ../libft/libft.a -lreadline

int	main(void)
{
	printf("===== PROMPT FUNCTIONS TEST SUITE =====\n\n");
	
	test_session_functions();
	test_user_functions();
	test_simplify_path();
	test_build_prompt();
	test_prompt();
	test_edge_cases();
	
	printf("All tests completed successfully!\n");
	printf("To check for memory leaks, run with Valgrind:\n");
	printf("valgrind --leak-check=full --show-leak-kinds=all ./prompt_test\n");
	
	return (0);
}
*/