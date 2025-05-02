/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:20:04 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 13:45:00 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parserft.h"

char	*ft_get_env(t_Env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) != 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_single_quotes(const char *line, int *i)
{
	int		start;
	char	*content;

	start = ++(*i);
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	content = ft_substr(line, start, *i - start);
	if (line[*i] == '\'')
		(*i)++;
	return (content);
}

char	*ft_exit_code(int *i, int last_exit)
{
	char	*exit_str;

	exit_str = ft_itoa(last_exit);
	*i += 2;
	return (exit_str);
}

char	*ft_variable(const char *line, int *i, t_Env *env)
{
	int		start;
	char	*key;
	char	*value;
	char	*dup;

	start = ++(*i);
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	key = ft_substr(line, start, *i - start);
	value = ft_get_env(env, key);
	if (value)
		dup = ft_strdup(value);
	else
		dup = ft_strdup("");
	free(key);
	return (dup);
}

char	*ft_append(char *result, char c)
{
	char	buf[2];
	char	*join;

	buf[0] = c;
	buf[1] = '\0';
	join = ft_strjoin_free(result, buf);
	return (join);
}
