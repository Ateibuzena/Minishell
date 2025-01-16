#include "../minishellft.h"

int main(int argc, char **argv, char **envp)
{
    char *prompt;
    char *input;
    t_History *history;
    t_Env *env;

    (void)argc;
    (void)argv;
    // Copiar el entorno y asignar memoria para el historial
    env = ft_copy_env(envp);
    history = (t_History *)malloc(sizeof(t_History));
    if (!history)
        return (perror("Error al asignar memoria para el historial"), 1);
    ft_init_history(history);
    while (1)
    {
        // Construir el prompt
        prompt = ft_build_prompt(env);
        input = readline(prompt);
        free(prompt);
        // Salir si la entrada es NULL (Ctrl+D)
        if (input == NULL)
            break ;
        // Procesar entrada si no está vacía
        if (ft_strlen(input) > 0)
        {
            /*if (ft_strchr(input, '|')) // Si hay un pipe
                ft_process_pipes(input, history, env);
            else // Si no hay pipes*/
                ft_process_command(input, history, &env);
        }
        free(input);      
    }
    ft_free_history(history);
    ft_free_env(env);
    return (0);
}
