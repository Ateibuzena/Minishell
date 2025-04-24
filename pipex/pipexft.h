/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:13:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/23 19:40:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEXFT_H
# define PIPEXFT_H

# include "../libft/libft.h"
# include "../builtins/builtinsft.h"
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <aio.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>


# define MIN_ARGS 5
# define READ 0
# define WRITE 1

typedef struct s_par
{
	int	i;
	int	j;
}	t_par;

typedef struct s_command
{
	char	**cmd;       // Ej: {"cat", NULL}
	char	*infile;     // Ej: "infile" si hay redirección "< infile"
	char	*outfile;    // Ej: "outfile" si hay redirección "> outfile"
	char	*heredoc;    // Ej: "heredoc" si hay redirección "<< heredoc"
	int		append;      // 1 si ">>", 0 si ">"
}	t_command;

typedef struct s_executor
{
	t_command	**commands;
	int			count;     // número de comandos en el pipeline
}	t_executor;

/*pipex_execute.c*/
char		*resolve_path(char *cmd, char **env);
pid_t		execute_pipeline(t_executor *exec, t_Env *env, t_History *history);

/*pipex_parse.c*/
t_command	*init_command(void);
t_executor	*parse_commands(char **argv);

/*pipex_utils.c*/
int			ft_here_doc(char *delimiter);
char		*ft_strjoin_free(char *s1, char *s2);
char		**env_to_array(t_Env *env);

/*pipex_error.c*/
void		ft_perror(const char *str);
void		ft_errno(char *argument);

/*pipex_free.c*/
void		free_executor(t_executor *exec);
void		free_partial_executor(t_executor *exec);

/*pipex.c*/
int			ft_pipex(char **input, t_Env *env, t_History *history);

#endif
