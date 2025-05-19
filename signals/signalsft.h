/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalsft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:28:51 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/17 19:55:12 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALSFT_H
# define SIGNALSFT_H

# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

extern volatile sig_atomic_t	g_exit;

/*signals_sigint.c*/
void	sigint_handler(int sig);

/*signals_sigtstp.c*/
void	sigtstp_handler(int sig);

/*signals_sigquit.c*/
void	sigquit_handler(int sig);

/*signals_sigterm.c*/
void	sigterm_handler(int sig);

/*signals_sigchld.c*/
void	sigchld_handler(int sig);

/*signals_sigwinch.c*/
void	sigwinch_handler(int sig);

/*signals.c*/
int		*get_g_in_readline(void);
void	ft_setup_signals(void);

#endif
