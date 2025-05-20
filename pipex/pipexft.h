/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:13:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 20:00:33 by azubieta         ###   ########.fr       */
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
	int			len;
	int			fd[2];
	int			prev_fd;
	t_executor	*exec;
	t_History	*history;
	t_Env		**env;
	char		**env_array;
	pid_t		last_pid;
	int			last_status;
}	t_pipex;

/*pipex_init.c*/
t_command	*ft_init_command(int len);
t_executor	*ft_init_executor(int len);

/*pipex_redcirect.c*/
int			ft_handle_input(t_pipex *pipex);
int			ft_handle_output(t_pipex *pipex);
void		ft_handle_dup2(t_pipex *pipex, int infile, int outfile);

/*pipex_execute_utils.c*/
int			ft_setup_pipe(t_pipex *pipex);
pid_t		ft_fork_process(void);
void		ft_close_fds(t_pipex *pipex);
void		ft_execute_builtin_or_error(t_pipex *pipex, t_command *cmd);
void		ft_execute_external(t_pipex *pipex, t_command *cmd);

/*pipex_execute.c*/
char		*ft_path_env(char **env);
char		*ft_resolve_path(char *cmd, char **env);
void		ft_execute(t_pipex *pipex);
void		ft_child_process(t_pipex *pipex);
pid_t		ft_process_pipeline(t_pipex *pipex);

/*pipex_parse.c*/
t_executor	*ft_parse_commands(char **argv);

/*pipex_utils.c*/
int			ft_count_vars(t_Env *env);
int			ft_here_doc(char *delimiter);
char		**ft_envtoarray(t_Env *env);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_cmd_not_found(t_pipex *pipex, t_command *cmd);

/*pipex_error.c*/
void		ft_perror(const char *str);
void		ft_errno(char *argument);

/*pipex_free.c*/
void		ft_free_command(t_command *cmd, int len);
void		ft_free_executor(t_executor *exec, int len);
void		ft_free_pipex(t_pipex *pipex);

/*pipex.c*/
int			ft_pipex(char **input, t_Env**env, t_History *history);

#endif
