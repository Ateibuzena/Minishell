/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promptft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:02:32 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/03 15:01:42 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPTFT_H
# define PROMPTFT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../builtins/builtinsft.h"

# define S(x) "\001" x "\002"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define PINK "\033[35m"
# define YELLOW "\033[33m"
# define RESET   "\033[0m"

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