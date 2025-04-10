#include "./builtinsft.h"

int main(void)
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
    ft_echo(args1, env);

    // Test cd
    ft_cd(args2);

    // Test pwd
    ft_pwd();

    // Test export
    ft_export(&env, args4);

    // Test unset
    ft_unset(&env, args5);

    // Test env
    ft_env(env, args6);

    // Test exit
    ft_exit(args7);

    // Free environment variables
    ft_free_env(env);

    // Free history (if applicable)
    ft_free_history(history);

    return 0;
}
