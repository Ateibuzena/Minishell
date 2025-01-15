#ifndef PROMPT_H
# define PROMPT_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../builtins/builtinsft.h"

/*prompt_session.c*/
char *ft_find_session(char *value);
char *ft_extract_session(t_env *env);

/*prompt_user.c*/
char *ft_find_user(t_env *env);
char *ft_extract_user(t_env *env);

/*prompt_build.c*/
char *ft_simplify_path(char *cwd);
char *ft_build_prompt(t_env *env);

# endif