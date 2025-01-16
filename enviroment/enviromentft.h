/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromentft.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:47:10 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/16 13:03:53 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENTFT_H
# define ENVISROMENTFT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

// Definición de la estructura para almacenar variables de entorno
typedef struct s_Env
{
    char *key;
    char *value;
    struct s_Env *next;
} t_Env;

/*enviroment_free.c*/
void    ft_free_env(t_Env *env_list);

/*enviroment_init.c*/
t_Env   *ft_copy_env(char **envp);

/*enviroment_utils*/
void    ft_split_env(const char *env_entry, char **key, char **value);
t_Env   *ft_create_node(const char *key, const char *value);
void    ft_add_node(t_Env **env_list, t_Env *new_node);
void    ft_delete_env(t_Env **head, const char *key);
void    ft_add_env(t_Env **env, const char *key, const char *value);

#endif