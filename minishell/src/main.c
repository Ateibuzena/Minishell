#include "../minishellft.h"

int bash(int argc, char *argv[], char *envp[])
{
    char *bash_path = "/bin/bash";
    char *bash_argv[] = {bash_path, NULL};  // Argumentos para execve (bash sin opciones)

    while (1) 
    {
        printf("Ejecutando /bin/bash...\n");

        // Ejecutar /bin/bash con el entorno actual
        if (execve(bash_path, bash_argv, envp) == -1) 
        {
            perror("Error en execve");
            sleep(1);  // Espera 1 segundo antes de reintentar
        }
    }

    return 0;  // Nunca se ejecutará porque execve reemplaza el proceso
}

int main(int argc, char **argv, char **envp)
{
    char *prompt;
    char *input;
    t_History *history;
    t_Env *env;

    (void)argc;
    (void)argv;
    //CONFIGURAR SEÑALES
    // Copiar el entorno y asignar memoria para el historial
    env = ft_copy_env(envp);
    
    history = (t_History *)malloc(sizeof(t_History));
    if (!history)
    return (ft_perror("Malloc error: History\n"), 1);
    ft_init_history(history);
    while (1)
    {
        // Construir el prompt
        prompt = ft_build_prompt(env);
        input = readline(prompt);
        fprintf(stderr, "\nInput: %s\n", input);
        free(prompt);
        // Salir si la entrada es NULL (Ctrl+D)
        if (input == NULL)
            break ;
        // Procesar entrada si no está vacía
        if (ft_strlen(input) > 0)
        {
            char *cleaned;

            cleaned = ft_handle_quotes(input);
            /*if (ft_strcmp(input, "./minishell"))
            {
                ft_export(env, )
            }*/
            if (!cleaned)
                break ;
            fprintf(stderr, "\nSin comillas: %s\n", cleaned);
            if (ft_strchr(cleaned, '|') || !ft_is_builtins(cleaned)) // Si hay un pipe
                ft_handle_pipes(cleaned, history, envp);
            else // Si no hay pipes
                ft_handle_builtin(cleaned, history, &env);
            free(cleaned);    
        }
        free(input); 
    }
    ft_free_history(history);
    ft_free_env(env);
    return (0);
}
