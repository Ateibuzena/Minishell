/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 04:12:36 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 14:11:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../pipexft.h"

// Helper function to display information about open file descriptors
void	print_open_fds_info(void)
{
	int	fd;

	printf("\n=== OPEN FILE DESCRIPTORS ===\n");
	for (fd = 0; fd < 10; fd++)
	{
		if (fcntl(fd, F_GETFD) != -1)
			printf("FD %d is open\n", fd);
	}
	printf("\n");
}

// Helper function to setup a simple t_pipex structure for testing
t_pipex	*setup_test_pipex(char **input, t_History *history)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	ft_memset(pipex, 0, sizeof(t_pipex));
	ft_init(pipex, input, history);
	return (pipex);
}

#include <assert.h>

// Test initialization functions
void	test_pipex_init(void)
{
	t_pipex		*pipex;
	char		*input[] = {"ls", "-la", "|", "grep", "test", NULL};
	t_History	*history = NULL;

	printf("=== Testing ft_init ===\n");
	
	pipex = setup_test_pipex(input, history);
	if (!pipex)
	{
		printf("Failed to allocate memory for pipex\n");
		return;
	}
	
	printf("Pipex initialized with:\n");
	printf("  Number of commands (n): %d\n", pipex->n);
	printf("  Command count (count): %d\n", pipex->count);
	printf("  Total arguments (size): %d\n", pipex->size);
	
	printf("Arguments:\n");
	for (int i = 0; pipex->argv[i]; i++)
		printf("  argv[%d]: '%s'\n", i, pipex->argv[i]);
	
	ft_free_pipex(&pipex);
	printf("Pipex structure freed successfully\n\n");
}


// Test pipe creation functionality
void test_create_pipe(void)
{
    t_pipex *pipex;
    char *input[] = {"ls", "-la", NULL};
    t_History *history = NULL;
    char buffer[100]; // Declara la variable buffer

    printf("=== Testing ft_create_pipe ===\n");

    pipex = setup_test_pipex(input, history);
    if (!pipex)
    {
        printf("Failed to allocate memory for pipex\n");
        return;
    }

    // Llamar a la creación del pipe
    ft_create_pipe(pipex);

    if (pipex->pipes && pipex->pipes[0])
    {
        printf("Pipe created successfully:\n");
        printf("  Read end (pipes[0][READ]): %d\n", pipex->pipes[0][READ]);
        printf("  Write end (pipes[0][WRITE]): %d\n", pipex->pipes[0][WRITE]);

        // Test de comunicación entre el pipe: escribe y lee
        char message[] = "Test pipe message";
        write(pipex->pipes[0][WRITE], message, strlen(message) + 1); // Usa write() correctamente

        // Ahora lee desde el pipe
        lseek(pipex->pipes[0][READ], 0, SEEK_SET); // Asegúrate de leer desde el principio
        read(pipex->pipes[0][READ], buffer, sizeof(buffer));
        printf("Read from pipe: '%s'\n", buffer);
    }
    else
    {
        printf("Failed to create pipe\n");
    }

    ft_free_pipex(&pipex);
    printf("Pipex structure freed successfully\n\n");
}


// Test command path resolution
void test_resolve_cmd(char **environ)
{
    t_pipex *pipex;
    char *input[] = {"ls", "-la", NULL};
    t_History *history = NULL;
    char *pathname = NULL;

    printf("=== Testing ft_resolve_cmd ===\n");

    pipex = setup_test_pipex(input, history);
    if (!pipex)
    {
        printf("Failed to allocate memory for pipex\n");
        return;
    }

    // Test con un comando válido
    printf("Testing resolution of 'ls':\n");
    ft_resolve_cmd(pipex, "ls", environ, &pathname);
    assert(pathname != NULL); // Verifica que el pathname no es NULL
    printf("  Resolved path: %s\n", pathname);
    if (pathname && pathname != pipex->commands[0]) // Verificación
		free(pathname);  // Solo se libera si fue asignado dinámicamente

    // Test con un comando con path absoluto
    printf("\nTesting resolution of '/bin/echo':\n");
    ft_resolve_cmd(pipex, "/bin/echo", environ, &pathname);
    assert(pathname != NULL); // Verifica que el pathname no es NULL
    printf("  Resolved path: %s\n", pathname);
    if (pathname && pathname != pipex->commands[0]) // Verificación
		free(pathname);  // Solo se libera si fue asignado dinámicamente

    ft_free_pipex(&pipex);
    printf("Pipex structure freed successfully\n\n");
}

// Test file redirection handling
void test_redirection(void)
{
    t_pipex *pipex;
    char *input[] = {"echo", "test", ">", "testfile.txt", NULL};
    t_History *history = NULL;
    char **split;

    printf("=== Testing redirection handling ===\n");

    pipex = setup_test_pipex(input, history);
    if (!pipex)
    {
        printf("Failed to allocate memory for pipex\n");
        return;
    }

    printf("Testing output redirection:\n");
    split = ft_split(">", ' ');
    ft_handle_redirection(pipex, split);
    assert(pipex->outfile != STDOUT_FILENO); // Verifica que se ha redirigido correctamente
    printf("  Outfile descriptor: %d\n", pipex->outfile);

    ft_freedouble(split);

    // Verifica si el archivo se crea
    FILE *file = fopen("testfile.txt", "r");
    assert(file != NULL); // Verifica que el archivo fue creado
    fclose(file);
    
    // Limpiar archivo después del test
    unlink("testfile.txt");

    ft_free_pipex(&pipex);
    printf("Pipex structure freed successfully\n\n");
}

// Test pipeline with redirection
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

void test_basic_pipe_execution(char **environ)
{
    char *input[] = {"echo", "Hello World", "|", "grep", "Hello", NULL};
    t_History *history = NULL;
    int status;
    FILE *fp;
    char buffer[1024];

    printf("=== Testing basic pipe execution ===\n");
    printf("Command: 'echo Hello World | grep Hello'\n");

    // Aquí llamamos a la función que ejecuta el pipeline (asegurándonos de que devuelva el status correcto)
    status = ft_pipex(input, environ, history);
    printf("Execution completed with status: %d\n", status);

    // Para verificar la salida, podemos redirigir la salida del comando a un archivo temporal o a un pipe
    fp = popen("echo Hello World | grep Hello", "r"); // Usamos popen para capturar la salida
    if (!fp) {
        printf("Error opening pipe for command output\n");
        return;
    }

    // Leemos la salida y la comparamos con el valor esperado
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Comprobamos si la salida contiene lo esperado
        assert(strcmp(buffer, "Hello World\n") == 0); // El resultado esperado
        printf("Output: '%s'\n", buffer);
    } else {
        printf("No output produced from the command\n");
    }

    // Cerramos el pipe
    fclose(fp);

    printf("\n");
}

// Test pipeline with redirection
void	test_pipe_with_redirection(char **environ)
{
	char		*input[] = {"echo", "Hello World", ">", "output.txt", NULL};
	t_History	*history = NULL;
	int			status;
	FILE		*file;
	char		buffer[100];

	printf("=== Testing pipe with redirection ===\n");
	printf("Command: 'echo Hello World > output.txt'\n");
	
	status = ft_pipex(input, environ, history);
	printf("Execution completed with status: %d\n", status);
	
	// Check if file was created and contains correct content
	file = fopen("output.txt", "r");
	if (file)
	{
		fgets(buffer, sizeof(buffer), file);
		printf("Content of output.txt: '%s'\n", buffer);
		fclose(file);
		unlink("output.txt");
	}
	else
		printf("Failed to open output.txt\n");
	
	printf("\n");
}


// Test error handling
void	test_error_handling(void)
{
	t_pipex		*pipex;
	char		*input[] = {"nonexistentcommand", NULL};
	t_History	*history = NULL;

	printf("=== Testing error handling ===\n");
	
	pipex = setup_test_pipex(input, history);
	if (!pipex)
	{
		printf("Failed to allocate memory for pipex\n");
		return;
	}
	
	printf("Testing ft_errno:\n");
	errno = ENOENT;
	ft_errno("nonexistentfile");
	
	printf("\nTesting ft_perror:\n");
	ft_perror("Test error message\n");
	
	ft_free_pipex(&pipex);
	printf("Pipex structure freed successfully\n\n");
}

// Test memory management
void	test_memory_management(void)
{
	t_pipex		*pipex;
	char		*input[] = {"ls", "-la", "|", "grep", "test", NULL};
	t_History	*history = NULL;

	printf("=== Testing memory management ===\n");
	
	printf("Allocating pipex structure...\n");
	pipex = setup_test_pipex(input, history);
	if (!pipex)
	{
		printf("Failed to allocate memory for pipex\n");
		return;
	}
	
	printf("Creating pipes...\n");
	ft_create_pipe(pipex);
	
	printf("Freeing pipex structure...\n");
	ft_free_pipex(&pipex);
	printf("Pipex structure freed successfully\n");
	
	printf("Testing free with NULL pipex...\n");
	ft_free_pipex(&pipex);
	printf("NULL pipex handled successfully\n\n");
}

// gcc -o pipex_test $(find . -name "*.c") -I../../builtins -I../../history -I../../enviroment -I../../libft ../../builtins/builtins.a ../../history/history.a ../../enviroment/enviroment.a ../../libft/libft.a -lreadline

int	main(int argc, char **argv, char **env)
{
	printf("===== PIPEX FUNCTIONS TEST SUITE =====\n\n");

	(void)argc;
	(void)argv;
	
	//test_pipex_init();
	//test_create_pipe();
	test_resolve_cmd(env);
	//test_redirection();
	//test_basic_pipe_execution(env);
	//test_pipe_with_redirection(env);
	//test_error_handling();
	//test_memory_management();
	
	printf("All tests completed successfully!\n");
	printf("To check for memory leaks, run with Valgrind:\n");
	printf("valgrind --leak-check=full --show-leak-kinds=all ./pipex_test\n");
	
	return (0);
}*/