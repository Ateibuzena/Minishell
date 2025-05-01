/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:14 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 16:46:58 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../signalsft.h"

int *get_g_in_readline(void)
{
    static int g_in_readline = 0;
    return (&g_in_readline);
}

void setup_signals()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGTERM, sigterm_handler);
    signal(SIGCHLD, sigchld_handler);
    signal(SIGWINCH, sigwinch_handler);

}
