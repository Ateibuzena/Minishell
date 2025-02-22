#include "../minishellft.h"


void ft_handle_pipes(char *input, t_History *history, char **env)
{
    char **commands;
    char *entry;
    int status;

    entry = ft_strdup(input);
    ft_add_entry(history, entry);
    free(entry);
    commands = ft_group_tokens(input); //cambio group for split?
    if (!commands)
        return ft_perror("Pipex error: Tokens\n");
    status = ft_pipex(commands, env, history);
    fprintf(stderr, "\nft_pipex retornó: %d\n", status); // Depuración
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
        printf("token: %s\n", token);
        args[i++] = token;
        token = ft_strtok(NULL, " ");
    }
    args[i] = NULL;
	if (!args[0])
		ft_perror("Builtins error: Tokens\n");
}

void ft_handle_builtin(char *input, t_History *history, t_Env **env)
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
        printf("inputs: %s\n", input);
        entry = ft_strjoin(entry, args[i]);
		temp = entry;
        entry = ft_strjoin(entry, " ");
		free(temp);
        i++;
    }
    ft_add_entry(history, entry);
    ft_execute_builtins(args, history, env);
    free(entry);
}
