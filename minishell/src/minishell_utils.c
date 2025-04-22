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

static int ft_handle_redirections(char **argv, int *saved_stdin, int *saved_stdout)
{
    int i = 0;
    int fd;

    *saved_stdin = dup(STDIN_FILENO);
    *saved_stdout = dup(STDOUT_FILENO);

    while (argv[i])
    {
        if (!ft_strncmp(argv[i], "<", 1))
        {
            fd = open(argv[i] + 2, O_RDONLY);
            if (fd == -1)
            {
                perror(argv[i] + 2);
                return (-1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (!ft_strncmp(argv[i], ">", 1))
        {
            fd = open(argv[i] + 2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror(argv[i] + 2);
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (!ft_strncmp(argv[i], ">>", 2))
        {
            fd = open(argv[i] + 3, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                perror(argv[i] + 3);
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        i++;
    }
    return (0);
}


void ft_handle_pipes(char *input, t_History *history, t_Env *env)
{
    char    **argv;
    int     status;
    int     i;
    int     builtin;

    if (!input || !input[0])
        return (ft_perror("Pipex error: NULL input\n"));
    
    argv = ft_group_tokens(input);
    if (!argv || !argv[0] || !argv[0][0])
        return (ft_perror("Pipex error: Tokens\n"));
    
    // Si hay pipes, pasamos a pipex
    if (ft_strchr(input, '|'))
    {
        fprintf(stderr, "\nPipex con pipes: %s\n", argv[0]);
        status = ft_pipex(argv, env, history);
    }
    else
    {
        // Comprobamos si el comando es un builtin
        i = 0;
        builtin = -1;
        while (argv[i])
        {
            // Verificamos si hay redirecciones
            if (argv[i][0] && (argv[i][0] != '|' || argv[i][0] != '<' || argv[i][0] != '>'))
            {
                char **split = ft_split(argv[i], ' ');
                if (ft_is_builtins(split[0]))
                {
                    //builtin = 1;
                    builtin = i;
                    
                    break;
                }
            }
            i++;
        }

        // Si es un builtin, ejecutamos en el padre
        int stdin_backup;
        int stdout_backup;

        if (builtin > -1)
        {
            fprintf(stderr, "\nBuiltins: %s\n", argv[builtin]);
            if (ft_handle_redirections(argv, &stdin_backup, &stdout_backup) == -1)
                return (ft_freedouble(argv));

            char **split = ft_split(argv[builtin], ' ');
            status = ft_execute_builtins(split, history, &env);
            ft_freedouble(split);

            // Restaurar stdin y stdout originales
            dup2(stdin_backup, STDIN_FILENO);
            dup2(stdout_backup, STDOUT_FILENO);
            close(stdin_backup);
            close(stdout_backup);
        }
        else
        {
            fprintf(stderr, "pipex con un comando: %s\n", argv[0]);
            status = ft_pipex(argv, env, history);
        }
    }

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
