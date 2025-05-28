/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanin <chanin@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:47:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/28 17:14:44 by chanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_free_getnextline_bonus(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (ptr);
}

static char	*ft_buffer_update(char *buffer)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (ft_free_getnextline_bonus(buffer));
	ptr = malloc(((ft_strlen_getnextline_bonus(buffer) - i)
				+ 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		ptr[j++] = buffer[i++];
	ptr[j] = '\0';
	free(buffer);
	buffer = NULL;
	return (ptr);
}

static char	*ft_line_extract(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read_fd(int fd, char *buffer)
{
	char	*ptr;
	char	*temp;
	int		bytes;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (!ft_strchr_getnextline_bonus(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, ptr, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (ft_free_getnextline_bonus(ptr));
		}
		ptr[bytes] = '\0';
		temp = buffer;
		buffer = ft_strjoin_getnextline_bonus(buffer, ptr);
		free(temp);
		if (!buffer)
			return (ft_free_getnextline_bonus(ptr));
	}
	free(ptr);
	return (buffer);
}

char	*get_next_line_bonus(int fd)
{
	static t_fdnode	*list;
	t_fdnode		*current;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (ft_freenode_getnextline_bonus(&list, fd), NULL);
	current = list;
	while (current && current->fd != fd)
		current = current->next;
	if (!current)
	{
		current = ft_newnode_getnextline_bonus(fd);
		if (!current)
			return (NULL);
		current->next = list;
		list = current;
	}
	current->buffer = ft_read_fd(fd, current->buffer);
	if (!current->buffer)
		return (ft_freenode_getnextline_bonus(&list, fd));
	line = ft_line_extract(current->buffer);
	current->buffer = ft_buffer_update(current->buffer);
	if (!current->buffer)
		ft_freenode_getnextline_bonus(&list, fd);
	return (line);
}
