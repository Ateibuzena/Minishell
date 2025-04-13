/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokensft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:19:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 21:51:59 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENSFT_H
# define TOKENSFT_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include "../libft/libft.h"
# include "../builtins/builtinsft.h"

# define INITIAL_CAPACITY 10
# define MAX_TOKENS 100

# ifndef S_TOKEN
#  define S_TOKEN

typedef struct s_token
{
	int			capacity;
	char		**result;
	const char	*start;
	const char	*current;
	int			i;
}	t_token;

# endif

# ifndef S_GROUP
#  define S_GROUP

typedef struct s_group
{
	char	**input;
	char	**result;
	int		i;
	int		j;
}	t_group;

# endif

/*ft_snprintf.c*/
void	ft_snprintf(char *result,
			int length, const char *str1, const char *str2);

/*tokens_utils_split.c*/
char	*ft_process_double_delimiter(const char *current);
char	*ft_process_token(const char *start, const char *current);
char	*ft_process_delimiter(const char *current);
char	**ft_resize_result(char **result, int *capacity);
int		ft_handle_delimiter(const char **current, char **result, int i);

/*tokens_utils_tokenizer.c*/
int		ft_is_redirect(const char *token);
char	*ft_process_redirect(char **input, int *i);
char	*ft_process_pipe(char **input, int *i);
char	*ft_process_command(char **input, int *i);
void	ft_remove_pipes(char **result);

/*tokens_group_split.c*/
char	**ft_split_command(const char *input);
char	**ft_group_tokens(char *entry);

#endif