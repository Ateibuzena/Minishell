/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:34:24 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 19:25:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

static char	*ft_get_env(t_Env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) != 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*char	*ft_expand_variables(const char *arg, t_Env *env)
{
	char	*value;
	char	*result;

	if (!arg)
		return (NULL);

	if (arg[0] == '$')
	{
		value = ft_get_env(env, arg + 1);
		if (value)
			return (ft_strdup(value));
		else
			return (ft_strdup(""));
	}
	else if (arg[0] == '~')
	{
		result = ft_get_env(env, "HOME");
		if (result)
			return (ft_strjoin(result, arg + 1));
		else
			return (ft_strdup(arg));
	}
	return (ft_strdup(arg));
}*/

static char *ft_strjoin_free(char *s1, const char *s2)
{
	char *joined = ft_strjoin(s1, s2);
	free(s1);
	return joined;
}


char	*ft_expand_variables(const char *line, t_Env *env, int last_exit)
{
	int		i = 0;
	bool	in_single = false;
	bool	in_double = false;
	char	*result = ft_strdup("");

	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
		{
			int	start = ++i;
			while (line[i] && line[i] != '\'')
				i++;
			result = ft_strjoin_free(result, ft_substr(line, start, i - start));
			if (line[i]) i++; // cerrar comilla
		}
		else if (line[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (line[i] == '$' && !in_single && line[i + 1])
		{
			if (line[i + 1] == '?')
			{
				char *exit_code = ft_itoa(last_exit);
				result = ft_strjoin_free(result, exit_code);
				i += 2;
			}
			else
			{
				int	start = ++i;
				while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
					i++;
				char *key = ft_substr(line, start, i - start);
				char *value = ft_get_env(env, key);
				result = ft_strjoin_free(result, value ? value : "");
				free(key);
			}
		}
		else
		{
			char buf[2] = { line[i++], 0 };
			result = ft_strjoin_free(result, buf);
		}
	}
	return result;
}
