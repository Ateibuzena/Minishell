/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:42:38 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/12 22:32:23 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../enviromentft.h"

//gcc -o env_test $(find . -name "*.c") -I../../enviroment -I../../libft ../../enviroment/enviroment.a ../../libft/libft.a -lreadline

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

// Test ft_split_env function
void	test_split_env(void)
{
	char	*key;
	char	*value;

	printf("=== Testing ft_split_env ===\n");
	
	// Test normal case
	ft_split_env("HOME=/Users/user", &key, &value);
	printf("Normal case: '%s'='%s'\n", key, value);
	free(key);
	free(value);
	
	// Test no value
	ft_split_env("PATH", &key, &value);
	printf("No value case: '%s'='%s'\n", key, value ? value : "(null)");
	free(key);
	free(value);
	
	// Test empty value
	ft_split_env("TEST=", &key, &value);
	printf("Empty value case: '%s'='%s'\n", key, value ? value : "(null)");
	free(key);
	free(value);

	// Test NULL input (should handle gracefully)
	ft_split_env(NULL, &key, &value);
	printf("NULL input case handled\n");

	printf("\n");
}

// Test node creation and list operations
void	test_node_operations(void)
{
	t_Env	*env_list;
	t_Env	*node;

	printf("=== Testing node operations ===\n");
	env_list = NULL;

	// Test creating nodes
	node = ft_create_node("HOME", "/Users/user");
	printf("Created node: %s=%s\n", node->key, node->value);
	ft_add_node(&env_list, node);
	
	node = ft_create_node("PATH", "/usr/bin:/bin");
	printf("Created node: %s=%s\n", node->key, node->value);
	ft_add_node(&env_list, node);
	
	node = ft_create_node("USER", "azubieta");
	printf("Created node: %s=%s\n", node->key, node->value);
	ft_add_node(&env_list, node);
	
	// Test with NULL value
	node = ft_create_node("EMPTY", NULL);
	printf("Created node with NULL value: %s=%s\n", node->key, node->value ? node->value : "(null)");
	ft_add_node(&env_list, node);
	
	// Print the list
	print_env_list(env_list);
	
	// Test delete
	printf("Deleting USER...\n");
	ft_delete_env(&env_list, "USER");
	print_env_list(env_list);
	
	// Test add_env function
	printf("Adding SHELL=/bin/bash...\n");
	ft_add_env(&env_list, "SHELL", "/bin/bash");
	print_env_list(env_list);
	
	// Free the list
	ft_free_env(env_list);
	printf("Environment list freed.\n\n");
}

// Test ft_copy_env function
void	test_copy_env(void)
{
	char	*mock_env[] = {
		"HOME=/Users/azubieta",
		"PATH=/usr/bin:/bin",
		"USER=azubieta",
		"LANG=en_US.UTF-8",
		"TERM=xterm-256color",
		"SHELL=/bin/bash",
		NULL
	};
	t_Env	*env_list;

	printf("=== Testing ft_copy_env ===\n");
	env_list = ft_copy_env(mock_env);
	printf("Copied environment:\n");
	print_env_list(env_list);
	
	// Test modifying the copied environment
	printf("Adding new environment variable...\n");
	ft_add_env(&env_list, "TESTVAR", "testvalue");
	print_env_list(env_list);
	
	printf("Deleting PATH...\n");
	ft_delete_env(&env_list, "PATH");
	print_env_list(env_list);
	
	// Free the list
	ft_free_env(env_list);
	printf("Environment list freed.\n\n");
}

// Test edge cases
void	test_edge_cases(void)
{
	t_Env	*env_list;
	
	printf("=== Testing edge cases ===\n");
	env_list = NULL;
	
	// Test with empty list
	printf("Testing delete on empty list...\n");
	ft_delete_env(&env_list, "NONEXISTENT");
	printf("Empty list after delete attempt (should still be empty)\n");
	print_env_list(env_list);
	
	// Test NULL key attempt
	printf("Testing node creation with NULL key...\n");
	t_Env *null_node = ft_create_node(NULL, "value");
	if (!null_node)
		printf("Node creation with NULL key properly returned NULL\n");
	
	// Test adding NULL node
	printf("Testing add_node with NULL node...\n");
	ft_add_node(&env_list, NULL);
	printf("List after adding NULL node (should still be empty):\n");
	print_env_list(env_list);
	
	ft_free_env(env_list);
	printf("Edge case tests completed.\n\n");
}

int	main(void)
{
	printf("===== ENVIRONMENT FUNCTIONS TEST SUITE =====\n\n");
	
	test_split_env();
	test_node_operations();
	test_copy_env();
	test_edge_cases();
	
	printf("All tests completed successfully!\n");
	printf("If running with Valgrind, check for memory leaks.\n");
	return (0);
}
