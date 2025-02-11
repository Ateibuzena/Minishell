#include "../minishell/minishellft.h"


int ft_execute(char **args, t_History *history, t_Env **env)
{
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