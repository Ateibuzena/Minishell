#include "../minishellft.h"

int main()
{
    // Crear la lista de historial
    t_History *history_2;
    // Variable para almacenar la entrada del usuario
    char *input;
    // Inicializar una lista de variables de entorno (si es necesario)
    t_env *env;
    // Para almacenar los argumentos del comando

    env = NULL;

    // Asignar memoria para el historial y inicializarlo
    history_2 = (t_History *)malloc(sizeof(t_History));
    if (!history_2)
    {
        perror("Error al asignar memoria para el historial");
        return (1);
    }
    ft_init_history(history_2);

    printf("Bienvenido al minishell. Escribe 'exit' para salir o pulsa Ctrl+D.\n");

    // Bucle principal para simular la entrada de comandos
    while (1)
    {
        input = readline(">>> ");
        
        if (input == NULL)
        {  
            // Salir si el usuario presiona Ctrl+D
            printf("Adiós.\n");
            break;
        }

        if (ft_strlen(input) > 0)
        {
            char *args[100];
            /*PARSEAR ARGS*/
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
