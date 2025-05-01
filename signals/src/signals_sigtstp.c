/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigtstp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:50 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 16:33:33 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../signalsft.h"

void sigtstp_handler(int sig)
{
    (void)sig;
    write(1, "\nProcess suspended. Type 'fg' to resume.\n", 42); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
