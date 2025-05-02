/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:14 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 21:18:17 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../signalsft.h"

volatile sig_atomic_t g_exit = 0;

int	*get_g_in_readline(void)
{
	static int	g_in_readline = 0;

	return (&g_in_readline);
}

void	ft_setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTERM, sigterm_handler);
	signal(SIGCHLD, sigchld_handler);
	signal(SIGWINCH, sigwinch_handler);
}
