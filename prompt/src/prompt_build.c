/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/01 13:13:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../promptft.h"

char	*ft_simplify_path(char *cwd)
{
	char	*simplified;
	char	*home;

	home = getenv("HOME");
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
		simplified = malloc(ft_strlen(cwd) - ft_strlen(home) + 2);
		if (!simplified)
			return (NULL);
		simplified[0] = '~';
		ft_strcpy(simplified + 1, cwd + ft_strlen(home));
		return (simplified);
	}
	return (ft_strdup(cwd));
}

char	*ft_build_prompt(char *prompt, char *user, char *session, char *path)
{
	ft_strcpy(prompt, user);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, session);
	ft_strcat(prompt, ":");
	ft_strcat(prompt, path);
	ft_strcat(prompt, "$ ");
	free(user);
	free(session);
	free(path);
}

char	*ft_prompt(t_Env *env)
{
	char	*user;
	char	*session;
	char	*prompt;
	char	*cwd;
	char	*path;

	user = ft_extract_user(env);
	session = ft_extract_session(env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(user), free(session), NULL);
	path = ft_simplify_path(cwd);
	if (!user || !session || !path)
		return (free(user), free(session), free(cwd), free(path), NULL);
	prompt = malloc(ft_strlen(user) + ft_strlen(session) + ft_strlen(path) + 8);
	if (!prompt)
		return (free(user), free(session), free(cwd), free(path), NULL);
	ft_build_prompt(prompt, user, session, path);
	free(cwd);
	return (prompt);
}
