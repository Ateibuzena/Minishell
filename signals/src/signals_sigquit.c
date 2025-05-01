/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigquit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:24:57 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 16:33:00 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../signalsft.h"

void sigquit_handler(int sig)
{
    (void)sig;
    write(1, "Quit (core dumped)\n", 19);
}
