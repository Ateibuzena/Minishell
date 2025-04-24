/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:42:24 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/24 17:33:35 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINSFT_H
# define BUILTINSFT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../enviroment/enviromentft.h"
# include "../history/historyft.h"

/*builtins_cd.c*/
int		ft_cd(char **args);

/*builtins_cd_utils.c*/
char	*ft_expand_tilde(const char *path);
int		ft_change_directory(char *path);
int		ft_change_home(void);
int		ft_change_oldpwd(char **args);
int		ft_expand_directory(const char *path);

/*builtins_clear*/
void	ft_clear(void);

/*builtins_echo.c*/
int		ft_echo(char **args);

/*builtins_env.c*/
int		ft_env(t_Env *env, char **args);

/*builtins_exit.c*/
int		ft_exit(char **args);

/*builtins_export.c*/
int		ft_export(t_Env **env, char **args);

/*builtins_pwd.c*/
int		ft_pwd(void);

/*builtins_unset.c*/
int		ft_unset(t_Env **env, char **args);

/*ft_strtok.c*/
char	*ft_strtok(char *str, const char *delim);

/*builtins_utils*/
//char	*ft_expand_variables(const char *arg, t_Env *env);
//char	*ft_expand_variables(const char *line, t_Env *env, int last_exit);

/*builtins_execute.c*/
int		ft_is_builtins(char *argv);
int		ft_execute_builtins(char **args, t_History *history, t_Env **env);

#endif