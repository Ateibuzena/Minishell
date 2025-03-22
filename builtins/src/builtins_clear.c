/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:32:17 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/22 14:34:18 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

// Esto imprime el código ANSI para limpiar la terminal
void	ft_clear(void)
{
	write(STDOUT_FILENO, "\033[H\033[J", 7);
}
