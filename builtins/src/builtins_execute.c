#include "../minishell/minishellft.h"

static void ft_print_argv(char **args)
{
    int i = 0;
    while (args[i])
    {
        fprintf(stderr, "comando[%d]: %s\n", i, args[i]);
        i++;
    }
}

int ft_execute_builtins(char **args, t_History *history, t_Env **env)
{
    fprintf(stderr, "Entro en execute_builtins con argv: \n");
    ft_print_argv(args);
    // Procesar comandos built-ins
    if (ft_strcmp(args[0], "echo"))
        ft_echo(args);
    else if (ft_strcmp(args[0], "cd"))
        ft_cd(args);
    else if (ft_strcmp(args[0], "clear")) 
        ft_clear();
    else if (ft_strcmp(args[0], "pwd"))
        ft_pwd();
    else if (ft_strcmp(args[0], "export"))
        ft_export(env, args);
    else if (ft_strcmp(args[0], "unset"))
        ft_unset(env, args);
    else if (ft_strcmp(args[0], "env"))
        ft_env(*env, args);
    else if (ft_strcmp(args[0], "exit"))
        ft_exit(args);
    else if (ft_strcmp(args[0], "history"))
        ft_show_history(history); // Mostrar historial
    else
    {
        printf("%s: Command not found\n", args[0]); //intentar ejecutar el comando externo like pipex?? o si es el historial pintar la linea correspondiente
    }
    return (1);
}

int	ft_is_builtins(char *argv)
{
	char	**args;

	args = ft_split(argv, ' ');
	// Procesar comandos built-ins
    if (ft_strcmp(args[0], "echo"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "cd"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "clear")) 
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "pwd"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "export"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "unset"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "env"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "exit"))
        return (ft_freedouble(args), 1);
    else if (ft_strcmp(args[0], "history"))
        return (ft_freedouble(args), 1);
    else
		return (ft_freedouble(args), 0);
}