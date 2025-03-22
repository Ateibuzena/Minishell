/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:30:53 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/22 14:20:23 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

// Expande el ~ al directorio HOME
static char *ft_expand_tilde(const char *path)
{
    char *home;
    char *expanded;

    if (!path)
        return (NULL);
    home = getenv("HOME");
    if (home && path[0] == '~')
    {
        expanded = malloc(ft_strlen(home) + ft_strlen(path)); // Ya hay '\0' en ft_strlen
        if (!expanded)
            return (NULL);
        ft_strcpy(expanded, home);
        ft_strcat(expanded, path + 1); // Añade lo que sigue después de '~'
        return (expanded);
    }
    return (ft_strdup(path)); // Retorna copia si no es '~'
}

// Función genérica para cambiar de directorio y actualizar las variables de entorno
static int	ft_change_directory(char *path)
{
    char	*old_pwd;
    char	*current_pwd;

    old_pwd = getenv("PWD"); // Puede ser NULL
    if (chdir(path) == 0)
    {
        current_pwd = getcwd(NULL, 0);
        if (current_pwd)
        {
            if (old_pwd)
                setenv("OLDPWD", old_pwd, 1); // Solo si es válido
            setenv("PWD", current_pwd, 1);
            free(current_pwd);
        }
        return (1);
    }
    ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
    ft_putstr_fd(path, STDERR_FILENO);
    ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
    return (0);
}

static int	ft_change_home(void)
{
    char	*home;
    
    home = getenv("HOME");
    if (home)
        return (ft_change_directory(home));
    ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
    return (-1); // Retornar -1 para indicar error
}

static int	ft_change_oldpwd(char **args)
{
    char	*old_pwd;
   
    if (args[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        return (-1);
    }
    old_pwd = getenv("OLDPWD");
    if (old_pwd)
    {
        if (ft_change_directory(old_pwd))
            return (ft_pwd()); // Solo ejecutamos `ft_pwd()` si `cd` tuvo éxito
        return (0);
    }
    ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
    return (-1);
}

static int	ft_expand_directory(const char *path)
{
    int		result;
    char	*expanded_path;

    if (!path)
        return (0);
    expanded_path = ft_expand_tilde(path);
    if (!expanded_path) // Validación extra
        return (0);
    result = ft_change_directory(expanded_path);
    free(expanded_path);
    return (result);
}

int	ft_cd(char **args)
{
    int	error;

    error = -1; // Inicialmente, asumimos error
    if (args[1] == NULL || (args[1][0] == '-' && args[1][1] == '-' && args[1][2] == '\0'))
        error = ft_change_home();
    else if (args[1][0] == '-' && args[1][1] == '\0')
        error = ft_change_oldpwd(args);
    else
        error = ft_expand_directory(args[1]);
    return (error);
}
