/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:34:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/30 15:38:54 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

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

char	*ft_expand_variables(const char *line, t_Env *env, int last_exit)
{
	int		i;
	bool	in_single;
	bool	in_double;
	char	*result;
	int		start;
	char	*exit_code;
	char 	*key;
	char 	*value;
	char 	buf[2];
	char	*temp;
	char *value_to_use;

	if (!line)
		return (NULL);
	i = 0;
	in_single = false;
	in_double = false;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
		{
			start = ++i;
			while (line[i] && line[i] != '\'')
				i++;
			temp = ft_substr(line, start, i - start);
			result = ft_strjoin_free(result, temp);
			free(temp);
			if (line[i])
				i++;
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
				exit_code = ft_itoa(last_exit);
				result = ft_strjoin_free(result, exit_code);
				free(exit_code);
				i += 2;
			}
			else
			{
				start = ++i;
				while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
					i++;
				key = ft_substr(line, start, i - start);
				value = ft_get_env(env, key);
				if (value)
					value_to_use = value;
				else
					value_to_use = "";
				result = ft_strjoin_free(result, value_to_use);
				free(key);
			}
		}
		else
		{
			buf[0] = line[i++];
			buf[1] = '\0';
			result = ft_strjoin_free(result, buf);
		}
	}
	return (result);
}
