/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promptft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:02:32 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/01 13:45:45 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPTFT_H
# define PROMPTFT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../builtins/builtinsft.h"

/*prompt_session.c*/
char	*ft_find_session(char *value);
char	*ft_extract_session(t_Env *env);

/*prompt_user.c*/
char	*ft_find_user(t_Env *env);
char	*ft_extract_user(t_Env *env);

/*prompt_build.c*/
char	*ft_simplify_path(char *cwd);
void	ft_build_prompt(char *prompt, char *user, char *session, char *path);
char	*ft_prompt(t_Env *env);

#endif