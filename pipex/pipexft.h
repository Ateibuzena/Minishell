/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:13:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/30 16:44:46 by azubieta         ###   ########.fr       */
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
	char	**cmd;
	char	*infile;
	char	*outfile;
	char	*heredoc;
	int		append;
}	t_command;

typedef struct s_executor
{
	t_command	**commands;
	int			count;
}	t_executor;

typedef struct s_pipex
{
	int			i;
	int			fd[2];
	int			prev_fd;
	t_executor	*exec;
	t_command	*cmd;
	t_History	*history;
	t_Env		**env;
	char		**env_array;
}	t_pipex;

/*pipex_init.c*/
t_command	*ft_init_command(void);
t_executor	*ft_init_executor(void);

/*pipex_redcirect.c*/
int			ft_handle_input(t_pipex *pipex);
int			ft_handle_output(t_pipex *pipex);
void		ft_handle_dup2(t_pipex *pipex, int infile, int outfile);

/*pipex_execute.c*/
char		*ft_path_env(char **env);
char		*ft_resolve_path(char *cmd, char **env);
void		ft_execute(t_pipex *pipex);
void		ft_child_process(t_pipex *pipex);
pid_t		ft_process_pipeline(t_pipex *pipex);

/*pipex_parse.c*/
t_executor	*ft_parse_commands(char **argv);

/*pipex_utils.c*/
int			ft_here_doc(char *delimiter);
char		**ft_envtoarray(t_Env *env);

/*pipex_error.c*/
void		ft_perror(const char *str);
void		ft_errno(char *argument);

/*pipex_free.c*/
void		ft_free_command(t_command *cmd);
void		ft_free_executor(t_executor *exec);
char		*ft_strjoin_free(char *s1, char *s2);

/*pipex.c*/
int			ft_pipex(char **input, t_Env *env, t_History *history);

#endif
