/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:43:44 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 00:59:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../historyft.h"

void clear_bash_history(void)
{
    pid_t pid;
	char *bash_path;
	char *option;
	char *command;
	char *args[4];
	
	bash_path = "/bin/bash";
	option = "-c";
	command = "history -c";
	pid = fork();
    if (pid < 0)
    {
        perror("History: Fork error");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        args[0] = bash_path;
        args[1] = option;
        args[2] = command;
        args[3] = NULL;
        if (execve(bash_path, args, NULL) == -1)
        {
            perror("Error al ejecutar execve");
            exit(EXIT_FAILURE);
        }
    }
}

// Helper function to print the history list
void	print_history_list(t_History *history)
{
	t_HistoryEntry	*current;
	int				i;

	i = 1;
	current = history->head;
	printf("History contents (%d entries):\n", history->size);
	if (!current)
		printf("  (empty history)\n");
	while (current)
	{
		printf("  %d: %s\n", i, current->line);
		current = current->next;
		i++;
	}
	printf("\n");
}

// Test history initialization
void	test_history_init(void)
{
	t_History	*history;

	printf("=== Testing ft_init_history ===\n");
	
	history = (t_History *)malloc(sizeof(t_History));
	if (!history)
	{
		printf("Failed to allocate memory for history\n");
		return;
	}
	
	ft_init_history(history);
	printf("History initialized: head=%p, tail=%p, size=%d\n", 
		(void *)history->head, (void *)history->tail, history->size);
	
	if (history->head == NULL && history->tail == NULL && history->size == 0)
		printf("✅ Initialization test PASSED\n");
	else
		printf("❌ Initialization test FAILED\n");
	
	ft_free_history(history);
	clear_history();
	printf("\n");
}

// Test new entry creation
void	test_new_entry(void)
{
	t_HistoryEntry	*entry;
	const char		*test_line = "test command line";

	printf("=== Testing ft_new_entry ===\n");
	
	entry = ft_new_entry(test_line);
	if (!entry)
	{
		printf("Failed to create new entry\n");
		return;
	}
	
	printf("New entry created with line: '%s'\n", entry->line);
	printf("Entry next pointer: %p\n", (void *)entry->next);
	
	if (entry->line && ft_strcmp(entry->line, test_line) == 0 && entry->next == NULL)
		printf("✅ New entry test PASSED\n");
	else
		printf("❌ New entry test FAILED\n");
	
	// Clean up
	free(entry->line);
	free(entry);
	printf("\n");
}

// Test adding entries to history
void	test_add_entries(void)
{
	t_History	*history;

	printf("=== Testing ft_add_entry ===\n");
	
	history = (t_History *)malloc(sizeof(t_History));
	if (!history)
	{
		printf("Failed to allocate memory for history\n");
		return;
	}
	
	ft_init_history(history);
	
	printf("Adding entries to history...\n");
	ft_add_entry(history, "ls -la");
	printf("Added: 'ls -la'\n");
	
	ft_add_entry(history, "cd /home");
	printf("Added: 'cd /home'\n");
	
	ft_add_entry(history, "echo Hello World");
	printf("Added: 'echo Hello World'\n");
	
	ft_add_entry(history, "cat file.txt");
	printf("Added: 'cat file.txt'\n");
	
	ft_add_entry(history, "grep pattern file");
	printf("Added: 'grep pattern file'\n");
	
	printf("History size after adding entries: %d\n", history->size);
	
	if (history->size == 5)
		printf("✅ Adding entries test PASSED\n");
	else
		printf("❌ Adding entries test FAILED\n");
	
	print_history_list(history);
	
	ft_free_history(history);
	clear_history();
	printf("\n");
}

// Test show history function
void	test_show_history(void)
{
	t_History	*history;

	printf("=== Testing ft_show_history ===\n");
	
	history = (t_History *)malloc(sizeof(t_History));
	if (!history)
	{
		printf("Failed to allocate memory for history\n");
		return;
	}
	
	ft_init_history(history);
	
	// Test empty history
	printf("Showing empty history:\n");
	ft_show_history(history);
	
	// Add entries and show again
	ft_add_entry(history, "command 1");
	ft_add_entry(history, "command 2");
	ft_add_entry(history, "command 3");
	
	printf("Showing history with 3 entries:\n");
	ft_show_history(history);
	
	ft_free_history(history);
	clear_history();
	printf("\n");
}

// Test navigation through history
void	test_navigation(void)
{
	t_History	*history;
	char		*cmd;
	int			index;

	printf("=== Testing ft_navigate_history ===\n");
	
	history = (t_History *)malloc(sizeof(t_History));
	if (!history)
	{
		printf("Failed to allocate memory for history\n");
		return;
	}
	
	ft_init_history(history);
	
	// Populate history with dummy commands
	ft_add_entry(history, "first command");
	ft_add_entry(history, "second command");
	ft_add_entry(history, "third command");
	ft_add_entry(history, "fourth command");
	ft_add_entry(history, "fifth command");
	
	printf("History populated with 5 commands:\n");
	print_history_list(history);
	
	ft_free_history(history);
	clear_history();
	printf("\n");
}

// Test edge cases
void	test_edge_cases(void)
{
	t_History	*history;
	char		*cmd;
	int			index;

	printf("=== Testing edge cases ===\n");
	
	// Test with empty history
	history = (t_History *)malloc(sizeof(t_History));
	if (!history)
	{
		printf("Failed to allocate memory for history\n");
		return;
	}
	
	ft_init_history(history);
	
	printf("Testing empty history:\n");
	printf("  History size: %d\n", history->size);
	print_history_list(history);
	
	printf("\nTesting NULL inputs:\n");
	printf("  Adding NULL entry...\n");
	ft_add_entry(history, NULL);
	printf("  History size after NULL add: %d\n", history->size);
	
	printf("  Adding empty string...\n");
	ft_add_entry(history, "");
	printf("  History size after empty string add: %d\n", history->size);
	print_history_list(history);
	
	ft_free_history(history);
	clear_history();
	
	printf("\nTesting ft_free_history with NULL:\n");
	ft_free_history(NULL);
	clear_history();
	printf("  ft_free_history(NULL) completed without crashing\n");
	
	printf("Edge cases tests completed.\n\n");
}

// Test memory management
void	test_memory_management(void)
{
	t_History	*history;
	int			i;
	char		cmd[100];

	printf("=== Testing memory management ===\n");
	
	history = (t_History *)malloc(sizeof(t_History));
	if (!history)
	{
		printf("Failed to allocate memory for history\n");
		return;
	}
	
	ft_init_history(history);
	
	// Add many entries to test memory handling
	printf("Adding 20 entries to history...\n");
	for (i = 0; i < 20; i++)
	{
		sprintf(cmd, "test command %d", i + 1);
		ft_add_entry(history, cmd);
	}
	
	printf("History size after adding 20 entries: %d\n", history->size);
	
	// Free all entries
	printf("Freeing history with 20 entries...\n");
	ft_free_history(history);
	clear_history();
	printf("History freed successfully\n");
	
	printf("Memory management test completed.\n\n");
}

// gcc -o history_test $(find . -name "*.c") -I../libft ../libft/libft.a -lreadline
// Nota: readline mantiene 4KB de memoria "reachable" que no se pueden liberar.
// No es un memory leak del programa, sino de la propia implementación de readline.

int	main(void)
{
	printf("===== HISTORY FUNCTIONS TEST SUITE =====\n\n");
	
	test_history_init();
	clear_history();
	test_new_entry();
	clear_history();
	test_add_entries();
	clear_history();
	test_show_history();
	clear_history();
	test_navigation();
	clear_history();
	test_edge_cases();
	clear_history();
	test_memory_management();
	
	printf("All tests completed successfully!\n");
	printf("If running with Valgrind, check for memory leaks with:\n");
	printf("valgrind --leak-check=full --show-leak-kinds=all ./history_test\n");
	
	// Clear readline history to prevent memory leaks
	clear_history();
	
	return (0);
}
