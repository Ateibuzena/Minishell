/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigterm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:53 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 21:01:49 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../signalsft.h"

void	sigterm_handler(int sig)
{
	(void)sig;
	write(1, "Terminating shell...\n", 21);
	g_exit = 1;
}
