/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/07 15:03:03 by azubieta         ###   ########.fr       */
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

void	ft_build_prompt(char *prompt, char *user, char *session, char *path)
{
	t_colors	colors;

	colors.user_color = PINK;
	colors.session_color = BLUE;
	colors.path_color = GREEN;
	colors.character_color = YELLOW;
	colors.reset_color = RESET;
	ft_strcpy(prompt, colors.user_color);
	ft_strcat(prompt, user);
	ft_strcat(prompt, colors.character_color);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, colors.session_color);
	ft_strcat(prompt, session);
	ft_strcat(prompt, colors.character_color);
	ft_strcat(prompt, ":");
	ft_strcat(prompt, colors.path_color);
	ft_strcat(prompt, path);
	ft_strcat(prompt, colors.character_color);
	ft_strcat(prompt, "$");
	ft_strcat(prompt, colors.reset_color);
	ft_strcat(prompt, " ");
}

int	ft_prompt_size(char *user, char *session, char *path)
{
	int	size;

	size = 0;
	size += ft_strlen(user);
	size += ft_strlen(session);
	size += ft_strlen(path);
	size += 1 + 1 + 1 + 1 + 1 + 2;
	size += 5 * 9;
	return (size);
}

char	*ft_prompt(t_Env *env)
{
	t_prompt	p;

	if (!env)
		return (NULL);
	p.user = ft_extract_user(env);
	if (!p.user)
		return (NULL);
	p.session = ft_extract_session(env);
	if (!p.session)
		return (free(p.user), NULL);
	p.cwd = getcwd(NULL, 0);
	if (!p.cwd)
		return (free(p.user), free(p.session), NULL);
	p.path = ft_simplify_path(p.cwd);
	free(p.cwd);
	if (!p.path)
		return (free(p.user), free(p.session), NULL);
	p.prompt_size = ft_prompt_size(p.user, p.session, p.path);
	p.prompt = malloc((p.prompt_size + 1) * sizeof(char));
	if (!p.prompt)
		return (free(p.user), free(p.session), free(p.path), NULL);
	ft_build_prompt(p.prompt, p.user, p.session, p.path);
	(free(p.user), free(p.session), free(p.path));
	return (p.prompt);
}
