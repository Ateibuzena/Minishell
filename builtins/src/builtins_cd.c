#include "../builtinsft.h"

// Función para manejar el comando cd
int ft_cd(char **args)
{
    if (args[1] == NULL)  // Si no hay argumento, se asume el directorio home
    {
        char *home = getenv("HOME");
        if (home)
            chdir(home);
        else
            fprintf(stderr, "minishell: cd: HOME not set\n");
    }
    else if (chdir(args[1]) != 0)  // Intentamos cambiar al directorio especificado
    {
        perror("minishell: cd");
    }
    return (1);
}
