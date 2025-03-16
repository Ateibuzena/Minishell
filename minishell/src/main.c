#include "../minishellft.h"

int main(int argc, char **argv, char **envp)
{
    //char *prompt;
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
        //prompt = ft_build_prompt(env);
        input = readline("\nminishola: $ ");
        fprintf(stderr, "\nInput: %s\n", input);
        //free(prompt);
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
