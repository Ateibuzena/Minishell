#include "../builtinsft.h"

// Función para manejar el comando pwd
int ft_pwd(void)
{
    char *cwd;
	
	cwd = getcwd(NULL, 0);  // Obtener el directorio actual
    if (cwd)
    {
        printf("%s\n", cwd);
        free(cwd);  // Liberar la memoria asignada por getcwd
    }
    else
    {
        perror("minishell: pwd");
    }
    return (1);
}
