/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promptft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:02:32 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/03 15:16:00 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPTFT_H
# define PROMPTFT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../builtins/builtinsft.h"

# define PINK "\001\033[35m\002"
# define BLUE "\001\033[34m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define RESET "\001\033[0m\002"

typedef struct s_colors
{
	char	*user_color;
	char	*session_color;
	char	*path_color;
	char	*character_color;
	char	*reset_color;
}	t_colors;

typedef struct s_prompt
{
	char	*user;
	char	*session;
	char	*prompt;
	char	*cwd;
	char	*path;
	int		prompt_size;
}	t_prompt;

/*prompt_session.c*/
char	*ft_find_session(char *value);
char	*ft_extract_session(t_Env *env);

/*prompt_user.c*/
char	*ft_find_user(t_Env *env);
char	*ft_extract_user(t_Env *env);

/*prompt_build.c*/
char	*ft_simplify_path(char *cwd);
void	ft_build_prompt(char *prompt, char *user, char *session, char *path);
int		ft_prompt_size(char *user, char *session, char *path);
char	*ft_prompt(t_Env *env);

#endif