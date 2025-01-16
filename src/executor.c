#include "../minishellft.h"

void ft_process_pipes(char *input, t_History *history)
{
    char **commands;
    char *entry;

    entry = ft_strdup(input);
    ft_add_entry(history, entry);
    free(entry);
    commands = ft_split(input, '|');
    if (!commands)
    {
        perror("Error al dividir los comandos para pipex");
        return ;
    }
    //ft_pipex(commands, env);
    ft_freedouble(commands);
}

void    ft_tokenize(char *input, char *args[])
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
}

int ft_execute(char **args, t_History *history, t_Env **env)
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
    return (1);
}

void ft_process_command(char *input, t_History *history, t_Env **env)
{
    char    *args[100];
    char    *entry;
    int     i;
    
    i = 0;
    ft_tokenize(input, args);
    if (!args[0])
        printf("error\n");
    entry = "";
    while (args[i])
    {
        entry = ft_strjoin(entry, args[i]);
        entry = ft_strjoin(entry, " ");
        i++;
    }
    ft_add_entry(history, entry);
    ft_execute(args, history, env);
    free(entry);
}
