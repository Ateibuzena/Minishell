/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:24:01 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/01 13:26:04 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokensft.h"

void	ft_snprintf(char *result,
			size_t length, const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_length;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	total_length = len1 + len2 + 1;
	if (total_length >= length)
		total_length = length - 1;
	ft_strcpy(result, str1);
	if (total_length > len1)
		ft_strcat(result, " ");
	if (total_length > len1 + 1)
		ft_strcat(result, str2);
	result[total_length] = '\0';
}

/*
### Explanation of `ft_snprintf`

1. **Calculating the total length**:
   - The total length is calculated by summing the lengths 
     of both strings, `str1` and `str2`, plus an additional 
     character for the space between them. 
     This determines the total length of the resulting string.

2. **Checking the available space**:
   - If the total length of the resulting string exceeds 
     the buffer's capacity (`length`), it is adjusted 
     to prevent overflow, ensuring there is space for 
     the null-terminating character `'\0'`.

3. **Copying the strings**:
   - First, `str1` is copied into `result`.
   - Then, a space is added between the two strings 
     if space allows.
   - After that, `str2` is concatenated to the result.

4. **String termination**:
   - Finally, it ensures that `result` ends with the 
     null character `'\0'`.

### Why do we use `ft_snprintf` in `ft_split_command`?

In the `ft_split_command` function, we use `ft_snprintf` 
to concatenate two strings (`input[i]` and `input[i + 1]`) 
with a space between them. This is useful when processing 
commands with multiple arguments that should be treated 
as a single token. By using `ft_snprintf`, we ensure that 
the strings are correctly concatenated within a controlled 
buffer and prevent memory overflow, as we manage 
the available space in the buffer.
*/
