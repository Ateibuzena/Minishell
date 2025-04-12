/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:42:38 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/12 21:46:04 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

/*int	main(void)
{
	char *args1[] = {"echo", "Hello", "World", NULL};
    char *args2[] = {"cd", "..", NULL};
    char *args3[] = {"pwd", NULL};
    char *args4[] = {"export", "TEST_VAR=42", NULL};
    char *args5[] = {"unset", "TEST_VAR", NULL};
    char *args6[] = {"env", NULL};
    char *args7[] = {"exit", "0", NULL};
    t_Env *env = NULL;
    t_History *history = NULL;

    // Initialize environment variables
    ft_add_env(&env, "HOME", "/home/user");
    ft_add_env(&env, "OLDPWD", "/home/user/old");
    
    // Test echo
    fprintf(stderr, "Test echo\n");
    ft_echo(args1, env);
    fprintf(stderr, "\n");
    
    // Test cd
    fprintf(stderr, "Test cd\n");
    ft_cd(args2);
    fprintf(stderr, "\n");
    
    // Test pwd
    fprintf(stderr, "Test pwd\n");
    ft_pwd();
    fprintf(stderr, "\n");
    
    // Test export
    fprintf(stderr, "Test export\n");
    ft_export(&env, args4);
    fprintf(stderr, "\n");

    // Test env
    fprintf(stderr, "Test env\n");
    ft_env(env, args3);
    fprintf(stderr, "\n");

    // Test unset
    fprintf(stderr, "Test unset\n");
    ft_unset(&env, args5);
    fprintf(stderr, "\n");

    // Test env
    fprintf(stderr, "Test env\n");
    ft_env(env, args6);
    fprintf(stderr, "\n");

    // Test exit
    fprintf(stderr, "Test exit\n");
    ft_exit(args7);
    fprintf(stderr, "\n");

    // Free environment variables
    ft_free_env(env);

    // Free history (if applicable)
    ft_free_history(history);
    return (0);
}*/
