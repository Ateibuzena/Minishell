/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:13:53 by azubieta          #+#    #+#             */
/*   Updated: 2024/12/28 15:25:35 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This header file contains declarations for various 
// functions and types defined in the "libft" library.
#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

// Definition of type t_size if not defined to libft
# ifndef T_SIZE
#  define T_SIZE

typedef unsigned int	t_size;

# endif

// Struct to ft_split
# ifndef COUNTERS
#  define COUNTERS

typedef struct Counters
{
	t_size		i;
	long int	sign;
	t_size		n;
	t_size		words;
}	t_Counters;

# endif

// Struct to ft_split
# ifndef POINTERS
#  define POINTERS

typedef struct Pointers
{
	char		**ptr;
	char		*temp;
}	t_Pointers;

# endif

//Struct to libft_bonus
# ifndef S_LIST_42
#  define S_LIST_42

typedef struct s_list_42
{
	void			*content;
	struct s_list_42	*next;
}	t_list_42;

# endif

// Struct to get_netx_line_bonus
# ifndef S_LIST
#  define S_LIST

typedef struct s_list
{
	char			*buffer;
	int				fd;
	struct s_list	*next;
}	t_list;

# endif

// Struct to ft_printf
# ifndef S_SPECIFIER
#  define S_SPECIFIER

typedef struct s_Specifier
{
	char	key;
	void	(*ft_ft)();
}	t_Specifier;

# endif

// Struct to ft_printf
# ifndef S_PRINTF
#  define S_PRINTF

typedef struct s_Printf
{
	int			count;
	int			i;
	t_Specifier	*specifier;
}	t_Printf;

# endif

// Buffer to get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 45
# endif

// Struct to ft_itoa
# ifndef ITOA
#  define ITOA

typedef struct Itoa
{
	long	i;
	char	*ptr;
	char	*temp;
	int		index;
}	t_Itoa;

# endif

/*SRC/D_ASCII/*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
bool	ft_isspace(char c);

/*SRC/D_FDS/*/
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*SRC/D_GET_NEXT_LINE/*/

char	*get_next_line(int fd);
char	*ft_read_fd(int fd, char *buffer);
char	*ft_line(char *line);
char	*ft_buffer_update(char *buffer);

char	*ft_free(char *ptr);
char	*get_next_line_bonus(int fd);
char	*ft_read_fd_bonus(int fd, char *buffer);
char	*ft_line(char *line);
char	*ft_buffer_update_bonus(char *buffer);
t_list	*ft_newnode(int fd);
char	*ft_freenode(t_list **list, int fd);

/*SRC/D_LISTS/*/

t_list_42	*ft_lstnew(void *ptr);
void		ft_lstadd_front(t_list_42 **lst, t_list_42 *new);
int			ft_lstsize(t_list_42 *lst);
t_list_42	*ft_lstlast(t_list_42 *lst);
void		ft_lstadd_back(t_list_42 **lst, t_list_42 *new);
void		ft_lstdelone(t_list_42 *lst, void (*del)(void *));
void		ft_lstclear(t_list_42 **lst, void (*del)(void *));
void		ft_lstiter(t_list_42 *lst, void (*f)(void *));
t_list_42	*ft_lstmap(t_list_42 *lst, void *(*f)(void *), void (*del)(void *));

/*SRC/D_MEMORY/*/

void		*ft_memset(void *array, int value, t_size len);
void		ft_bzero(void *array, t_size len);
void		*ft_memcpy(void *dst, const void *src, t_size n);
void		*ft_memmove(void *dst, const void *src, t_size len);
void		*ft_memchr(const void *s, int c, t_size n);
int			ft_memcmp(const void *s1, const void *s2, t_size n);
void		*ft_calloc(t_size count, t_size size);

/*SRC/D_PRINTF/*/

void		ft_call_putchar_printf(va_list *args, int fd, int *count);
void		ft_putchar_printf(char c, int fd, int *count);
void		ft_call_putstr_printf(va_list *args, int fd, int *count);
void		ft_putstr_printf(char *str, int fd, int *count);
void		ft_call_putnbr_printf(va_list *args, int fd, int *count);
void		ft_putnbr_printf(long int i, int fd, int *count);
void		ft_call_putnbr_u(va_list *args, int fd, int *count);
void		ft_putnbr_u(unsigned int i, int fd, int *count);
void		ft_call_puthex_upper(va_list *args, int fd, int *count);
void		ft_puthex_upper(unsigned int i, int fd, int *count);
void		ft_call_puthex_lower(va_list *args, int fd, int *count);
void		ft_puthex_lower(unsigned int i, int fd, int *count);
void		ft_call_puthex_nil(va_list *args, int fd, int *count);
void		ft_puthex_nil(unsigned long int i, int fd, int *count);
void		ft_call_putchar_percent(va_list *args, int fd, int *count);

/*SRC/D_STRINGS/*/

char		*ft_strncpy(char *dest, const char *src, size_t n);
long int	ft_strtol(const char *str, char **endptr, int base);
t_size		ft_strlen(const char *s);
t_size		ft_strlcpy(char *dst, const char *src, t_size dstsize);
t_size		ft_strlcat(char *dst, const char *src, t_size dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
int			ft_strncmp(const char *s1, const char *s2, t_size n);
char		*ft_strnstr(const char *hay, const char *need, t_size len);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, t_size len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_strcmp(const char *s1, const char *s2);

/*SRC/*/
int			ft_printf(char const *format, ...);
int			ft_atoi(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
void		ft_freedouble(char **ptr);
void		ft_freedouble_array(int **pipes, int len);
int			ft_strlen_double(char **str);
long int	ft_strtol(const char *str, char **endptr, int base);

// End of LIBFT_H
#endif
