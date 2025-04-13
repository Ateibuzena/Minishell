/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:11:16 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 21:56:14 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

/*// Helper function to print token arrays
void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
	{
		printf("  (tokens array is NULL)\n");
		return ;
	}
	if (!tokens[0])
		printf("  (empty tokens array)\n");
	while (tokens && tokens[i])
	{
		printf("  [%d]: '%s'\n", i, tokens[i]);
		i++;
	}
	printf("\n");
}

// Test ft_split_command function
void	test_split_command(void)
{
	char	**tokens;
	char	*test_inputs[] = {
		"ls -la",
		"echo hello world",
		"cat file.txt | grep pattern",
		"ls > output.txt",
		"cat < input.txt | sort | uniq > result.txt",
		"echo \"quoted string with spaces\"",
		"command with < redirections > and | pipes",
		"<< EOF cat",
		">> append.txt echo text",
		NULL
	};
	int		i;

	printf("=== Testing ft_split_command ===\n");
	
	i = 0;
	while (test_inputs[i])
	{
		printf("Input: '%s'\n", test_inputs[i]);
		tokens = ft_split_command(test_inputs[i]);
		printf("Tokens:\n");
		print_tokens(tokens);
		ft_freedouble(tokens);
		i++;
	}
	
	printf("\n");
}

// Test ft_group_tokens function
void	test_group_tokens(void)
{
	char	**grouped_tokens;
	char	*test_inputs[] = {
		"ls -la",
		"echo hello world",
		"cat file.txt | grep pattern",
		"ls > output.txt",
		"cat < input.txt | sort | uniq > result.txt",
		NULL
	};
	int		i;

	printf("=== Testing ft_group_tokens ===\n");
	
	i = 0;
	while (test_inputs[i])
	{
		printf("Input: '%s'\n", test_inputs[i]);
		grouped_tokens = ft_group_tokens(test_inputs[i]);
		printf("Grouped tokens:\n");
		print_tokens(grouped_tokens);
		ft_freedouble(grouped_tokens);
		i++;
	}
	
	printf("\n");
}

// Test ft_snprintf function
void	test_snprintf(void)
{
	char	buffer[100];
	
	printf("=== Testing ft_snprintf ===\n");
	
	ft_snprintf(buffer, sizeof(buffer), "Hello", "World");
	printf("Test 1: '%s'\n", buffer);
	
	ft_snprintf(buffer, sizeof(buffer), "Command", "with args");
	printf("Test 2: '%s'\n", buffer);
	
	ft_snprintf(buffer, 10, "This is", "too long for buffer");
	printf("Test 3 (truncation): '%s'\n", buffer);
	
	ft_snprintf(buffer, sizeof(buffer), "", "Empty first string");
	printf("Test 4: '%s'\n", buffer);
	
	ft_snprintf(buffer, sizeof(buffer), "Empty second string", "");
	printf("Test 5: '%s'\n", buffer);
	
	printf("\n");
}

// Test delimiter processing functions
void	test_delimiter_processing(void)
{
	char	*token;
	const char *input = "<";
	const char *double_input = "<<";
	int	i;
	char	**result;
	int	capacity = 10;

	printf("=== Testing delimiter processing ===\n");
	
	printf("Testing ft_process_delimiter:\n");
	token = ft_process_delimiter(input);
	printf("  Single delimiter: '%s'\n", token);
	free(token);
	
	printf("Testing ft_process_double_delimiter:\n");
	token = ft_process_double_delimiter(double_input);
	printf("  Double delimiter: '%s'\n", token);
	free(token);
	
	printf("Testing ft_handle_delimiter:\n");
	result = malloc(capacity * sizeof(char *));
	if (result)
	{
		i = 0;
		i = ft_handle_delimiter(&input, result, i);
		printf("  Handle delimiter returned i=%d\n", i);
		printf("  Result token: '%s'\n", result[0]);
		free(result[0]);
		free(result);
	}
	
	printf("\n");
}

// Test token processing functions
void	test_token_processing(void)
{
	char	*token;
	const char *start = "hello world";
	const char *current = start + 5; // Points to space
	
	printf("=== Testing token processing ===\n");
	
	printf("Testing ft_process_token:\n");
	token = ft_process_token(start, current);
	printf("  Processed token: '%s'\n", token);
	free(token);
	
	printf("\n");
}

// Test redirect and pipe processing functions
void	test_redirect_pipe_processing(void)
{
	char	**input;
	char	*token;
	int	i;
	
	printf("=== Testing redirect and pipe processing ===\n");
	
	printf("Testing ft_is_redirect:\n");
	printf("  Is '<' a redirect? %s\n", 
		ft_is_redirect("<") ? "Yes" : "No");
	printf("  Is '>' a redirect? %s\n", 
		ft_is_redirect(">") ? "Yes" : "No");
	printf("  Is '|' a redirect? %s\n", 
		ft_is_redirect("|") ? "Yes" : "No");
	
	// Setup test input
	input = malloc(3 * sizeof(char *));
	if (input)
	{
		input[0] = ft_strdup("<");
		input[1] = ft_strdup("file.txt");
		input[2] = NULL;
		
		printf("Testing ft_process_redirect:\n");
		i = 0;
		token = ft_process_redirect(input, &i);
		printf("  Processed redirect: '%s'\n", token);
		printf("  New index: %d\n", i);
		free(token);
		
		// Free input[0] and input[1] before resetting
		free(input[0]);
		free(input[1]); // Don't forget to free input[1]
		input[0] = ft_strdup("|");
		input[1] = NULL;
		
		printf("Testing ft_process_pipe:\n");
		i = 0;
		token = ft_process_pipe(input, &i);
		printf("  Processed pipe: '%s'\n", token);
		printf("  New index: %d\n", i);
		free(token);
		
		// Free input[0]
		free(input[0]);
		// Free input array itself
		free(input);
	}
	
	printf("\n");
}

// Test command processing 
void	test_command_processing(void)
{
	char	**input;
	char	*token;
	int	i;
	
	printf("=== Testing command processing ===\n");
	
	// Setup test input
	input = malloc(3 * sizeof(char *));
	if (input)
	{
		input[0] = ft_strdup("ls");
		input[1] = ft_strdup("-la");
		input[2] = NULL;
		
		printf("Testing ft_process_command:\n");
		i = 0;
		token = ft_process_command(input, &i);
		printf("  Processed command: '%s'\n", token);
		printf("  New index: %d\n", i);
		free(token);
		
		// Free input array
		free(input[0]);
		free(input[1]);
		free(input);
	}
	
	printf("\n");
}

// Test ft_remove_pipes function
void	test_remove_pipes(void)
{
	char	**tokens;
	
	printf("=== Testing ft_remove_pipes ===\n");
	
	tokens = malloc(5 * sizeof(char *));
	if (tokens)
	{
		tokens[0] = ft_strdup("command1");
		tokens[1] = ft_strdup("|");
		tokens[2] = ft_strdup("command2");
		tokens[3] = ft_strdup("|");
		tokens[4] = NULL;
		
		printf("Before ft_remove_pipes:\n");
		print_tokens(tokens);
		
		ft_remove_pipes(tokens);
		
		printf("After ft_remove_pipes:\n");
		print_tokens(tokens);
		
		// Free tokens array
		ft_freedouble(tokens);
	}
	
	printf("\n");
}

// Test overall token pipeline
void	test_token_pipeline(void)
{
	char	**split_tokens;
	char	**grouped_tokens;
	char	*test_command = "cat file.txt | grep pattern > output.txt";
	
	printf("=== Testing complete token pipeline ===\n");
	printf("Input command: '%s'\n", test_command);
	
	// Split command into tokens
	split_tokens = ft_split_command(test_command);
	printf("After ft_split_command:\n");
	print_tokens(split_tokens);
	
	// Group tokens by commands, redirects, etc.
	grouped_tokens = ft_group_tokens(test_command);
	ft_remove_pipes(grouped_tokens);
	printf("After ft_group_tokens:\n");
	print_tokens(grouped_tokens);
	
	// Free token arrays
	ft_freedouble(split_tokens);
	ft_freedouble(grouped_tokens);
	
	printf("\n");
}

// gcc -o tokens_test $(find . -name "*.c")
-I../../libft ../../libft/libft.a -lreadline
// Run all tests
int	main(void)
{
	printf("===== TOKENS FUNCTIONS TEST SUITE =====\n\n");
	
	test_split_command();
	test_group_tokens();
	test_snprintf();
	test_delimiter_processing();
	test_token_processing();
	test_redirect_pipe_processing();
	test_command_processing();
	test_remove_pipes();
	test_token_pipeline();
	
	printf("All tests completed successfully!\n");
	printf("To check for memory leaks, run with Valgrind:\n");
	printf("valgrind --leak-check=full --show-leak-kinds=all ./tokens_test\n");
	
	return (0);
}*/
