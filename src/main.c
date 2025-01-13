#include "../minishellft.h"




int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *prompt;
    char *args[100];

    t_History *history_2;

    char *input;

    t_env *env;

    env = ft_copy_env(envp);
    
    // Asignar memoria para el historial y inicializarlo
    history_2 = (t_History *)malloc(sizeof(t_History));
    if (!history_2)
        return (perror("Error al asignar memoria para el historial"), 1);
    ft_init_history(history_2);
    // Bucle principal para simular la entrada de comandos
    while (1)
    {
        prompt = ft_build_prompt(env);
        input = readline(prompt);
        if (input == NULL)
        {  
            printf("Adiós.\n");
            break;
        }

        if (ft_strlen(input) > 0)
        {
            int  i;
            char *token;

            i = 0;
            // Tokenizar la entrada
            token = ft_strtok(input, " ");
            while (token != NULL)
            {
                args[i++] = token;
                token = ft_strtok(NULL, " ");
            }
            args[i] = NULL; // Null-terminate the array de argumentos
            //parseo + tokenizacion = limpiar copia de historial
            // Agregar al historial
            i = 0;
            char *entry = ft_calloc(1, sizeof(char));
            while (args[i])
            {
                entry = ft_strjoin(entry, args[i]);
                entry = ft_strjoin(entry, " ");

                i++;
            }
            ft_add_entry(history_2, entry);
            
            ft_execute(args, history_2, &env);
        }

        // Liberar la memoria de la entrada
        free(input);
    }

    // Liberar la memoria del historial
    ft_free_history(history_2);
    
    return (0);
}
