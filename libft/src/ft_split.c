/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:31:55 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:28:59 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static struct Counters	ft_struct(t_size o, t_size t, t_size th, t_size f)
{
	t_Counters	sign_index;

	sign_index.i = o;
	sign_index.sign = t;
	sign_index.n = th;
	sign_index.words = f;
	return (sign_index);
}

static t_size	ft_wordscount(char const *s, char c)
{
	t_size	count;
	t_size	word;

	count = 0;
	word = 0;
	if (s[count] != c && s[count] != '\0')
		word++;
	while (s[count] != '\0')
	{
		if (s[count] == c && s[count + 1] != c && s[count + 1] != '\0')
			word++;
		count++;
	}
	if (s[count] == '\0' && word == 0)
		return (word);
	return (word);
}

static char	**ft_nullcase_split(char **pointer)
{
	ft_freedouble(pointer);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	t_Pointers	pointers;
	t_Counters	counters;

	counters = ft_struct(0, 0, 0, ft_wordscount(s, c));
	pointers.ptr = malloc((counters.words + 1) * sizeof(char *));
	if (pointers.ptr == NULL)
		return (NULL);
	while (counters.words--)
	{
		while (*s == c)
			s++;
		counters.n = 0;
		while (s[counters.n] != '\0' && s[counters.n] != c)
			counters.n++;
		pointers.temp = malloc((counters.n + 1) * sizeof(char));
		if (pointers.temp == NULL)
			return (ft_nullcase_split(pointers.ptr));
		ft_strlcpy(pointers.temp, s, counters.n + 1);
		pointers.ptr[counters.i++] = pointers.temp;
		pointers.temp = NULL;
		free(pointers.temp);
		s += counters.n;
	}
	pointers.ptr[counters.i] = 0;
	return (pointers.ptr);
}
/*
#include <stdio.h>
int main(void)
{
	char	*ptr = "   lorem   ipsum dolor     sit amet, c";
	char	**puntero;

	puntero = ft_split(ptr, ' ');
	for (int i = 0; i < 12; i++)
	{
		printf("%s\n", puntero[i]);
	}
	printf("%s", ptr);
	return (0);
}*/
