#include "../builtinsft.h"



// Expande el ~ al directorio HOME
static char *ft_expand_tilde(const char *path)
{
    char *home;
    char *expanded;

    if (!path)
        return (NULL);

    home = getenv("HOME");
    if (home && path[0] == '~') // Verifica si el path empieza con '~'
    {
        expanded = malloc(ft_strlen(home) + ft_strlen(path) + 1);  // +1 para el '\0'
        if (!expanded)
            return (NULL);
        ft_strcpy(expanded, home);          // Copia la ruta del home
        ft_strcat(expanded, path + 1);      // Añade el resto del path después de '~'
        return (expanded);
    }
    return (ft_strdup(path));  // Si no tiene '~', devuelve el path original
}

// Función genérica para cambiar de directorio y actualizar las variables de entorno
static int ft_change_directory(char *path)
{
    char *old_pwd;
    char *current_pwd;

    old_pwd = getenv("PWD");  // Guardar el directorio actual antes de cambiar
    if (chdir(path) == 0)
    {
        // Cambiamos al nuevo directorio, actualizamos PWD y OLDPWD
        current_pwd = getcwd(NULL, 0);  // Obtener el nuevo directorio
        if (current_pwd)
        {
            setenv("OLDPWD", old_pwd, 1);  // OLD-PWD debe ser el valor anterior
            setenv("PWD", current_pwd, 1); // PWD debe ser el valor del directorio actual
            free(current_pwd);  // Liberamos la memoria de getcwd
        }
        return (1);  // Cambio de directorio exitoso
    }

    ft_putstr_fd("minishell: cd: failed to change directory to ", STDERR_FILENO);
    ft_putstr_fd(path, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    return (0);  // Fallo al cambiar de directorio
}

static int ft_change_home(void)
{
    char *home;
    
    home = getenv("HOME");
    if (home)
        return (ft_change_directory(home));
    ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
    return (0);
}

static int ft_change_oldpwd(void)
{
    char *old_pwd;
    
    old_pwd = getenv("OLDPWD");
    if (old_pwd)
        return (ft_change_directory(old_pwd));  // Cambiar al directorio de OLDPWD
    ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
    return (0);
}

static int ft_expand_directory(const char *path)
{
    int result;
    char *expanded_path;

    if (!path)
        return (0);  // Si path es NULL, no hacer nada

    expanded_path = ft_expand_tilde(path);
    result = ft_change_directory(expanded_path);
    free(expanded_path);  // Liberamos la memoria al final
    return (result);
}

// Función para manejar el comando cd
int ft_cd(char **args)
{
    int error;
    
    error = 0; // Asumimos que el comando fallará por defecto
    if (args[1] == NULL)
        error = ft_change_home();  // Si no se proporciona argumento, ir al HOME
    else if (args[1][0] == '-' && args[1][1] == '\0')
    {
        error = ft_change_oldpwd();  // Si el argumento es "-", ir a OLDPWD
        ft_pwd();
    }
    else
        error = ft_expand_directory(args[1]);  // Expande el path y cambia de directorio

    // Si alguna de las funciones devuelve 0, indica que hubo un error
    return (error);
}
