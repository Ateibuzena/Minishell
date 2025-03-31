/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:43:49 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../promptft.h"

// Función para ~=/home/azubieta y /=/root"
char *ft_simplify_path(char *cwd)
{
    char *simplified;
    char *home;
    
    home = getenv("HOME");  // Obtener el directorio home del usuario
    if (!cwd)
        return (NULL);
    
    if (home && ft_strstr(cwd, home) == cwd)
    {
        if (ft_strlen(cwd) == ft_strlen(home))
        {
            simplified = malloc(2);
            if (!simplified)
                return (NULL);
            simplified[0] = '~';
            simplified[1] = '\0';
            return (simplified);
        }

        // Si está en un subdirectorio, reemplazar el inicio con "~"
        simplified = malloc(ft_strlen(cwd) - ft_strlen(home) + 2);  // +1 para "~" y +1 para '\0'
        if (!simplified)
            return (NULL);
        
        simplified[0] = '~';
        ft_strcpy(simplified + 1, cwd + ft_strlen(home));  // Copiar el resto de la ruta sin el `/`
        return (simplified);
    }
    return (ft_strdup(cwd)); // Duplicar cwd si no es /home
}

// Función para construir el string "<user>@<session_id>: <path>$ "
char *ft_build_prompt(t_Env *env)
{
    char *user;
    char *session;
    char *prompt;
    char *cwd;
    char *simplified;

    user = ft_extract_user(env);
    session = ft_extract_session(env);
    cwd = getcwd(NULL, 0);
    if (!cwd) // Si `getcwd` falla, evitamos llamadas innecesarias
        return (free(user), free(session), NULL);

    simplified = ft_simplify_path(cwd);
    if (!user || !session || !simplified)
        return (free(user), free(session), free(cwd), free(simplified), NULL);
    
    prompt = malloc(ft_strlen(user) + ft_strlen(session) + ft_strlen(simplified) + 7 + 1);
    if (!prompt)
        return (free(user), free(session), free(cwd), free(simplified), NULL);

    ft_strcpy(prompt, user);
    ft_strcat(prompt, "@");
    ft_strcat(prompt, session);
    ft_strcat(prompt, ":");
    ft_strcat(prompt, simplified);
    ft_strcat(prompt, "$ ");
    free(user);
    free(session);
    free(cwd);
    free(simplified);
    return (prompt);
}
