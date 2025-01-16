/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/16 15:38:49 by azubieta         ###   ########.fr       */
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
    // Reemplazar "home" por "~" en cualquier parte de la ruta
    if (home && ft_strstr(cwd, home) == cwd)
    {
        // Si la ruta comienza con el directorio home, simplificar la ruta
        if (ft_strlen(cwd) == ft_strlen(home))
        {
            // Si la ruta es exactamente HOME, devolver solo "~"
            simplified = malloc(2);  // "~" + '\0'
            if (!simplified)
                return (NULL);
            simplified[0] = '~';
            simplified[1] = '\0';
            return (simplified);
        }

        // Si está en cualquier subdirectorio de HOME, reemplazar la parte de HOME con "~"
        simplified = malloc(ft_strlen(cwd) - ft_strlen(home) + 2);  // +2 para "~" y el terminador nulo
        if (!simplified)
            return (NULL);
        
        simplified[0] = '~';
        simplified[1] = '/';
        ft_strcpy(simplified + 2, cwd + ft_strlen(home));  // Copiar el resto de la ruta después de HOME
        return (simplified);
    }
    // Si no contiene "home" ni "root", devolver la ruta tal cual
    return (ft_strdup(cwd));
}


// Función para construir el string "<user>@<session_id>: <path>$ "
char *ft_build_prompt(t_Env *env)
{
    char *user;
    char *session;
    char *prompt;
    char *cwd;

    user = ft_extract_user(env);
    session = ft_extract_session(env);
    cwd = getcwd(NULL, 0);
    if (!user || !session || !cwd)
        return (free(user), free(session), free(cwd), NULL);
    prompt = malloc((ft_strlen(user) + ft_strlen(session) + ft_strlen(cwd) + 7 + 1) * sizeof(char));
    if (!prompt)
		return (free(user), free(session), free(cwd), NULL);
    ft_strcpy(prompt, user);
    ft_strcat(prompt, "@");
    ft_strcat(prompt, session);
    ft_strcat(prompt, ":");
    ft_strcat(prompt, ft_simplify_path(cwd));
    ft_strcat(prompt, "$ ");
    free(user);
    free(session);
    free(cwd);
    return (prompt);
}