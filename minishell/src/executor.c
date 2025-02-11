#include "../minishellft.h"

void ft_pipes(char *input, t_History *history, char **env)
{
    char **commands;
    char *entry;

    entry = ft_strdup(input);
    ft_add_entry(history, entry);
    free(entry);
    commands = ft_group_tokens(input); //cambio group for split?
    if (!commands)
    {
        perror("Error al dividir los comandos para pipex");
        return ;
    }
    int i = 0;
    while (commands[i])
    {
        printf("commads: %s\n", commands[i]);
        i++;
    }
    ft_pipex(ft_strlen_double(commands), commands, env, history);
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

void ft_command(char *input, t_History *history, t_Env **env)
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
