/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:33:18 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:10:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static const char	*skip_whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\f' || *str == '\v')
		str++;
	return (str);
}

static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

static int	determine_base(const char **str, int base)
{
	if (base == 0)
	{
		if (**str == '0')
		{
			if (*(*str + 1) == 'x' || *(*str + 1) == 'X')
			{
				(*str) += 2;
				return (16);
			}
			else
			{
				(*str)++;
				return (8);
			}
		}
		return (10);
	}
	return (base);
}

static long int	convert_to_number(const char **str, int base)
{
	long int	result;
	int			digit;

	result = 0;
	while (**str)
	{
		if (ft_isdigit(**str))
			digit = **str - '0';
		else if (ft_isalpha(**str))
			digit = ft_tolower(**str) - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		(*str)++;
	}
	return (result);
}

long int	ft_strtol(const char *str, char **endptr, int base)
{
	int			sign;
	long int	result ;

	str = skip_whitespace(str);
	sign = handle_sign(&str);
	base = determine_base(&str, base);
	result = convert_to_number(&str, base);
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}
