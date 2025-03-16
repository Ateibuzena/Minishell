/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexft.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:13:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/16 21:24:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEXFT_H
# define PIPEXFT_H

# include "../libft/libft.h"
# include "../builtins/builtinsft.h"
# include <errno.h>
# include <sys/wait.h>
# include <aio.h>
# include <string.h>
# include <stdio.h>

# define MIN_ARGS 5
# define READ 0
# define WRITE 1

typedef struct s_par
{
	int	i;
	int	j;
}	t_par;

typedef struct s_pipex
{
	int		n;
	int		i;
	int		cmd;
	int		count;
	int		size;
	char	**argv;
	int		**pipes;
	pid_t	*pids;
	char	*found_way;
	char	**clean_paths;
	char	**commands;
	int		status;
	int		infile;
	int		outfile;
	t_History *history;
}	t_pipex;

/*SRC/*/

/*pipex_first_process.c*/
void	ft_first_process(t_pipex *pipex, char **env);

/*pipex_middle_process.c*/
void	ft_middle_process(t_pipex *pipex, char **env);

/*pipex_last_process.c*/
void	ft_last_process(t_pipex *pipex, char **env);

/*pipex_execute.c*/
char	*ft_find_env_value(const char *key, char **env, size_t len);
char	*ft_find_executable(char **paths, char *command);
void	ft_resolve_cmd(t_pipex *pipex, char *argv, char **env, char **pathname);
void	ft_execute_cmd(t_pipex *pipex, char *argv, char **env, char *pathname);
void	ft_execute(t_pipex *pipex, char **env);

/*pipex_utils.c*/
void	ft_close_pipes(t_pipex *pipex);
void 	ft_create_pipe(t_pipex *pipex);
void 	ft_handle_lecture(t_pipex *pipex, char **split);
void 	ft_handle_redirection(t_pipex *pipex, char **split);
int		ft_here_doc(char *delimiter);

/*pipex_error.c*/
void	ft_perror(const char *str);
void	ft_errno(char *argument);
int		ft_waitpid(pid_t pid);

/*pipex_init.c*/
void	ft_init(t_pipex *pipex, char *input[], t_History *history);

/*pipex_free.c*/
void	ft_free_pipex(t_pipex **pipex);

/*pipex.c*/
int	ft_pipex(char **input, char **env, t_History *history);

#endif
