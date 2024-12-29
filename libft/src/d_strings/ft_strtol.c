/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:33:18 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/04 21:38:07 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

// Función para saltar los espacios en blanco
static const char *skip_whitespace(const char *str)
{
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
				|| *str == '\f' || *str == '\v')
        str++;
    return str;
}

// Función para manejar el signo de la conversión
static int handle_sign(const char **str)
{
    int sign = 1;
    if (**str == '-')
	{
        sign = -1;
        (*str)++;
    }
	else if (**str == '+')
        (*str)++;
    return (sign);
}

// Función para determinar la base de la conversión
static int determine_base(const char **str, int base)
{
    if (base == 0)
	{
        if (**str == '0')
		{
            if (*(*str + 1) == 'x' || *(*str + 1) == 'X')
			{
                (*str) += 2;  // Saltar "0x" o "0X"
                return (16);     // Hexadecimal
            }
			else
			{
                (*str)++;      // Saltar "0"
                return (8);      // Octal
            }
        }
        return (10);  // Decimal
    }
    return (base);
}

// Función para manejar la conversión de caracteres a número
static long int convert_to_number(const char **str, int base)
{
    long int result = 0;
    int digit;

    while (**str)
	{
        if (ft_isdigit(**str))
            digit = **str - '0';
        else if (ft_isalpha(**str))
            digit = ft_tolower(**str) - 'a' + 10;
        else
            break;
        if (digit >= base)
            break;
        result = result * base + digit;
        (*str)++;
    }
    return (result);
}

long int ft_strtol(const char *str, char **endptr, int base)
{
    int 		sign;
	long int 	result ;
	
	str = skip_whitespace(str);  // Saltar espacios
    sign = handle_sign(&str);  // Manejar el signo
    base = determine_base(&str, base);  // Determinar la base
    result = convert_to_number(&str, base);  // Convertir a número
    if (endptr)
        *endptr = (char *)str;  // Apuntar al resto de la cadena
    return (result * sign);  // Retornar el valor con el signo
}