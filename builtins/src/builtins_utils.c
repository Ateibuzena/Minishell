#include "../builtinsft.h"

// Busca una variable en tu lista de entorno
static char *ft_get_env(t_Env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) != 0) // Si las claves coinciden
            return (env->value);
        env = env->next;
    }
    return (NULL); // No encontrada
}

char *ft_expand_variables(const char *arg, t_Env *env)
{
    char *value;
    char *result;

    if (arg[0] == '$')
    {
        value = ft_get_env(env, arg + 1); // Busca en tu lista
        if (value)
        {
            result = ft_strdup(value);
        }
        else
        {
            result = ft_strdup("");
        }
        return result;
    }
    return ft_strdup(arg);
}