#include "../minishellft.h"

// Función que gestiona las comillas y devuelve el string procesado
char *ft_handle_quotes(const char *input)
{
    t_quoteState state;
    size_t len;
    char *output;
    size_t j;
    size_t i;
    
    state = NO_QUOTE;
    len = strlen(input);
    output = malloc(len + 1); // Reservamos memoria
    if (!output)
        return NULL; // Control de error de memoria
    j = 0; // Índice para el output
    i = 0; 
    while(i < len)
    {
        char c = input[i];

        switch (state)
        {
            case NO_QUOTE:
                if (c == '\'')
                    state = SINGLE_QUOTE;
                else if (c == '\"')
                    state = DOUBLE_QUOTE;
                else
                    output[j++] = c;
                break;
            case SINGLE_QUOTE:
                if (c == '\'')
                    state = NO_QUOTE;
                else
                    output[j++] = c; // Copia literal
                break;
            case DOUBLE_QUOTE:
                if (c == '\"')
                    state = NO_QUOTE;
                else if (c == '\\' && i + 1 < len)

                    output[j++] = input[++i]; // Manejar escape en comillas dobles
                else
                    output[j++] = c;
                break;
        }
        i++;
    }
    output[j] = '\0'; // Terminamos el string
    return (output);
}

void ft_handle_pipes(char *input, t_History *history, t_Env *env)
{
    char **argv;
    char *exit;
    int status;

    argv = ft_group_tokens(input);
    if (!argv)
        return ft_perror("Pipex error: Tokens\n");
    exit = ft_strdup(argv[0]);
    if (!exit)
        return ft_perror("Pipex error: strdup\n");
    exit = ft_strtok(exit, " \t");
    if (!ft_strchr(input, '|') && ft_strcmp(exit, "exit"))
    {
        free(exit);
        ft_exit(argv);
    }
    free(exit);
    status = ft_pipex(argv, env, history);
    //fprintf(stderr, "\n");
    //fprintf(stderr, "ft_pipex retornó: %d\n", status); // Depuración
    (void)status;
    ft_freedouble(argv);
}
/*
void ft_handle_pipes(char *input, t_History *history, t_Env *env)
{

    char **commands;
 
    int status;

    
    commands = ft_group_tokens(input); //cambio group for split?
    if (!commands)
        return ft_perror("Pipex error: Tokens\n");
    //exit = ft_strtok(argv[0], " \t");
    if (!ft_strchr(input, '|') && ft_strcmp(commands[0], "exit"))
         ft_exit(commands);
    status = ft_pipex(commands, env, history);
  
    (void)status;
    ft_freedouble(commands);
    //ft_freedouble(argv);
}*/


/*void    ft_tokenize(char *input, char *args[])
{
    char    *token;
    int     i;
    
    i = 0;
    token = ft_strtok(input, " ");
    while (token != NULL)
    {
        args[i++] = token;
        token = ft_strtok(NULL, " ");
    }
    args[i] = NULL;
	if (!args[0])
		ft_perror("Builtins error: Tokens\n");
}*/

/*void ft_handle_builtin(char *input, t_History *history, t_Env **env)
{
    char    *args[100];
    char    *entry;
	char	*temp;
    int     i;
    
    i = 0;
    ft_tokenize(input, args);
    entry = "";
    while (args[i])
    {
        printf("\nargs[%d]: %s\n", i, args[i]);
        entry = ft_strjoin(entry, args[i]);
		temp = entry;
        entry = ft_strjoin(entry, " ");
		free(temp);
        i++;
    }
    fprintf(stderr, "\nentry: %s\n", entry);
    ft_add_entry(history, entry);
    ft_execute_builtins(args, history, env);
    free(entry);
}*/
