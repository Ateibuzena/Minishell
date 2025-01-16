/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/16 13:00:23 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../promptft.h"

// Función para ~=/home/azubieta y /=/root"
char *ft_simplify_path(char *cwd)
{
    char *simplified;
    char *home;

    home = getenv("HOME");
    if (home && !ft_strncmp(cwd, home, ft_strlen(home)))
    {
        // Si cwd es exactamente igual a home, devolver solo "~"
        if (cwd[ft_strlen(home)] == '\0')
        {
            simplified = malloc(2); // "~" + '\0'
            if (!simplified)
                return (NULL);
            simplified[0] = '~';
            simplified[1] = '\0';
            return (simplified);
        }

        simplified = malloc(ft_strlen(cwd) - ft_strlen(home) + 2);
        if (!simplified)
            return (NULL);
        simplified[0] = '~';
        simplified[1] = '/';
        ft_strcpy(simplified + 2, cwd + ft_strlen(home) + 1);
        return (simplified);
    }
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