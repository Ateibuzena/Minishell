#include "../minishellft.h"

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