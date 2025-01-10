#include "../minishellft.h"

static char *ft_extract_session(t_env *env)
{
    char *start;
    char *end;
    char *session_id;
    char *session_manager_value;

    // Recorrer la lista enlazada de variables de entorno
    while (env)
    {
        // Buscar la clave "SESSION_MANAGER"
        if (ft_strcmp(env->key, "SESSION_MANAGER"))
        {
            // Obtener el valor asociado a SESSION_MANAGER
            session_manager_value = env->value;

            // Buscar "local/" o "unix/" en el valor
            start = ft_strstr(session_manager_value, "local/");
            if (!start)
                start = ft_strstr(session_manager_value, "unix/");
            if (start)
                start += 6; // Longitud de "local/" o "unix/"

            // Buscar el siguiente delimitador (".42malaga.com")
            end = ft_strstr(start, ".42malaga.com");

            if (end)
            {
                // Crear una nueva cadena para almacenar el substring que queremos
                session_id = (char *)malloc(((end - start) + 1) * sizeof(char));  // +1 para el null-terminator
                if (session_id)
                {
                    ft_strncpy(session_id, start, (end - start)); // Copiar la subcadena
                    session_id[end - start] = '\0'; // Asegurarse de que esté terminada en null
                    return session_id;
                }
            }
        }

        // Avanzar al siguiente nodo de la lista
        env = env->next;
    }

    return NULL;  // Si no se encuentra la sesión o el formato no es correcto
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *session_id;
    char *args[100];
    // Crear la lista de historial
    t_History *history_2;
    // Variable para almacenar la entrada del usuario
    char *input;
    // Inicializar una lista de variables de entorno (si es necesario)
    t_env *env;

    env = ft_copy_env(envp);
    //ft_env(env, args);
    session_id = ft_extract_session(env);
    
    // Asignar memoria para el historial y inicializarlo
    history_2 = (t_History *)malloc(sizeof(t_History));
    if (!history_2)
    {
        perror("Error al asignar memoria para el historial");
        return (1);
    }
    ft_init_history(history_2);

    //printf("Bienvenido al minishell. Escribe 'exit' para salir o pulsa Ctrl+D.\n");

    // Bucle principal para simular la entrada de comandos
    while (1)
    {
        char *prompt = NULL;
        prompt = ft_strjoin("azubieta@", session_id);
        char *new_prompt = ft_strjoin(prompt, ":~$ ");
        free(prompt);  // Liberar la memoria previa
        prompt = new_prompt;
        input = readline(prompt);
        free(prompt);
        if (input == NULL)
        {  
            // Salir si el usuario presiona Ctrl+D
            printf("Adiós.\n");
            break;
        }

        if (ft_strlen(input) > 0)
        {
            
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
