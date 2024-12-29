#include "../minishellft.h"

// Función para manejar el comando echo
int ft_echo(char **args)
{
    int i;
    int newline;
	
	newline = 1;  // Suponer que agregaremos un salto de línea por defecto
	i = 1;
    // Comprobar si el primer argumento es -n
    if (args[i] && ft_strcmp(args[i], "-n"))
    {
        newline = 0;  // No imprimir salto de línea
        i++;  // Saltar el -n
    }

    // Imprimir los argumentos
    while (args[i] != NULL)
    {
        printf("%s", args[i]);
        if (args[i + 1] != NULL)
            printf(" ");  // Agregar espacio entre palabras
        i++;
    }

    // Si no es la opción -n, imprimir salto de línea
    if (newline)
        printf("\n");

    return (1);
}

// Función para manejar el comando cd
int ft_cd(char **args)
{
    if (args[1] == NULL)  // Si no hay argumento, se asume el directorio home
    {
        char *home = getenv("HOME");
        if (home)
            chdir(home);
        else
            fprintf(stderr, "minishell: cd: HOME not set\n");
    }
    else if (chdir(args[1]) != 0)  // Intentamos cambiar al directorio especificado
    {
        perror("minishell: cd");
    }
    return (1);
}

// Función para manejar el comando pwd
int ft_pwd(void)
{
    char *cwd;
	
	cwd = getcwd(NULL, 0);  // Obtener el directorio actual
    if (cwd)
    {
        printf("%s\n", cwd);
        free(cwd);  // Liberar la memoria asignada por getcwd
    }
    else
    {
        perror("minishell: pwd");
    }
    return (1);
}

// Función para manejar el comando export
int ft_export(t_env **env, char **args)
{
    if (args[1] != NULL)  // Si hay un argumento, agregar o modificar la variable
    {
        char *key = strtok(args[1], "=");
        char *value = strtok(NULL, "");

        if (key && value)
        {
            ft_add_env(env, key, value);  // Agregar la nueva variable al entorno
        }
        else
        {
            fprintf(stderr, "minishell: export: invalid argument\n");
            return 1;
        }
    }

    t_env *current = *env;
    while (current)
	{
        printf("export %s=%s\n", current->key, current->value);
        current = current->next;
    }

    return (1);
}


// Función para eliminar un nodo de la lista env
void ft_delete_env(t_env **head, const char *key)
{
    t_env *temp;
    t_env *prev;

	prev = NULL;
	temp = *head;
    // Si la primera variable es la que queremos eliminar
    if (temp != NULL && strcmp(temp->key, key) == 0)
	{
        *head = temp->next;  // Mover la cabeza
        free(temp->key);
        free(temp->value);
        free(temp);
        return ;
    }

    // Buscar la variable que queremos eliminar
    while (temp != NULL && strcmp(temp->key, key) != 0)
	{
        prev = temp;
        temp = temp->next;
    }

    // Si la variable no fue encontrada
    if (temp == NULL)
	{
        printf("Variable de entorno no encontrada: %s\n", key);
        return ;
    }

    // Desenlazamos y liberamos la memoria
    prev->next = temp->next;
    free(temp->key);
    free(temp->value);
    free(temp);
}

// Función para agregar una variable de entorno a la lista
void ft_add_env(t_env **env, const char *key, const char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    t_env *current = *env;

    if (!new_node)
	{
        perror("Error al agregar variable de entorno");
        exit(1);
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    if (*env == NULL)
	{
        *env = new_node;
    } 
	else
	{
        while (current->next)
		{
            current = current->next;
        }
        current->next = new_node;
    }
}

// Función para manejar el comando unset
int ft_unset(t_env **env, char **args)
{
    if (args[1] == NULL)
	{
        fprintf(stderr, "minishell: unset: expected argument\n");
        return (1);
    }

    // Recorrer y eliminar las variables de entorno
    for (int i = 1; args[i] != NULL; i++) {
        ft_delete_env(env, args[i]);
    }

    return (1);
}

// Función para manejar el comando env
int ft_env(t_env *env, char **args)
{
    // Si se pasa un argumento adicional, mostrar un error
    if (args[1] != NULL)
    {
        fprintf(stderr, "minishell: env: no arguments allowed\n");
        return (1);
    }

    // Si la lista de variables de entorno está vacía, también mostrar un mensaje de error
    if (env == NULL)
    {
        fprintf(stderr, "minishell: env: no environment variables found\n");
        return (1);
    }

    // Recorremos la lista de variables de entorno e imprimimos en el formato "KEY=value"
    t_env *current = env;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    return (1);
}

// Función para manejar el comando exit
int ft_exit(char **args)
{
    int status = 0;

    if (args[1] != NULL)  // Si se proporciona un argumento, usarlo como código de salida
    {
        status = ft_atoi(args[1]);
    }

    exit(status);
}

// Función para ejecutar los built-ins
int ft_execute(char **args, t_History *history, t_env **env)
{
    // Procesar comandos built-ins
    if (ft_strcmp(args[0], "echo")) //parseo: impar comillas simples = here_doc && falta mirar gestion comillas dobles limpiar espacios antes de arg1
        ft_echo(args);
    else if (ft_strcmp(args[0], "cd")) //parseo: comillas simple parece ser igual que el echo
        ft_cd(args);
    else if (ft_strcmp(args[0], "pwd")) //parseo a args[0];
        ft_pwd();
    else if (ft_strcmp(args[0], "export"))
        ft_export(env, args);
    else if (ft_strcmp(args[0], "unset"))
        ft_unset(env, args);
    else if (ft_strcmp(args[0], "env"))
        ft_env(*env, args);
    else if (ft_strcmp(args[0], "exit"))
    {
        ft_exit(args);
        exit(0); // Terminar el programa
    }
    else if (ft_strcmp(args[0], "history"))
        ft_show_history(history); // Mostrar historial
    else
    {
        printf("%s: Command not found\n", args[0]); //intentar ejecutar el comando externo like pipex?? o si es el historial pintar la linea correspondiente
    }

    /*// Si no es un built-in, intentar ejecutar el comando externo like pipex??
    pid_t pid = fork();
    if (pid == 0)  // Si es el proceso hijo
    {
        execvp(args[0], args);  // Intentar ejecutar el comando externo
        perror("minishell");  // Si no se puede ejecutar, mostrar error
        exit(1);
    }
    else if (pid < 0)  // Si no se puede hacer fork
    {
        perror("minishell");
    }
    else  // Si es el proceso padre, esperar a que el hijo termine
    {
        wait(NULL);
    }*/

    return (1);
}
