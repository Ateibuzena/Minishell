/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:25:00 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 16:49:00 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../signalsft.h"

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    if (*get_g_in_readline())
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

