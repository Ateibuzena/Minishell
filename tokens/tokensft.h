#ifndef TOKENSFT_H
# define TOKENSFT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../builtins/builtinsft.h"

# define INITIAL_CAPACITY 10

void ft_snprintf(char *result, size_t length, const char *str1, const char *str2);


char *ft_process_token(const char *start, const char *current);
char *ft_process_delimiter(const char *current);
char **ft_resize_result(char **result, size_t *capacity);
char **ft_split_command(const char *input);

char **ft_group_tokens(char *entry);
void ft_remove_pipes(char **result);

# endif