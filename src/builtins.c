#include "../minishellft.h"

int ft_is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo"))
        return (1);
    else if (ft_strcmp(cmd, "cd"))
        return (1);
    else if (ft_strcmp(cmd, "pwd"))
        return (1);
    else if (ft_strcmp(cmd, "export"))
        return (1);
    else if (ft_strcmp(cmd, "unset"))
        return (1);
    else if (ft_strcmp(cmd, "env"))
        return (1);
    else if (ft_strcmp(cmd, "exit"))
        return (1);
    else if (ft_strcmp(cmd, "history"))
        return (1);
    else
        return (0);
}

int ft_execute(char **args, t_History *history, t_env **env)
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

    /*// Si no es un built-in, intentar ejecutar el comando externo like pipex??
    pid_t pid = fork();
    if (pid == 0)  // Si es el proceso hijo
    {
        execvp(args[0], args);  // Intentar ejecutar el comando externo
        perror("minishell");  // Si no se puede ejecutar, mostrar error
        exit(1);
    }
    else if (pid < 0)  // Si no se puede hacer fork
    {
        perror("minishell");
    }
    else  // Si es el proceso padre, esperar a que el hijo termine
    {
        wait(NULL);
    }*/

    return (1);
}
