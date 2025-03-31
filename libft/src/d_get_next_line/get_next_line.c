/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:47:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 18:53:04 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_buffer_update(char *buffer)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (NULL);
	ptr = malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		ptr[j++] = buffer[i++];
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
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

char	*ft_read_fd(int fd, char *buffer)
{
	char	*ptr;
	int		bytes;
	char	*temp;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while ((!buffer) || (!ft_strchr(buffer, '\n') && bytes != 0))
	{
		bytes = read(fd, ptr, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free(ptr));
		ptr[bytes] = '\0';
		temp = buffer;
		buffer = ft_strjoin(buffer, ptr);
		free(temp);
		if (!buffer)
			return (ft_free(ptr));
	}
	free(ptr);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer == NULL)
	{
		buffer = malloc(1 * sizeof(char));
		if (!buffer)
		{
			free(buffer);
			return (NULL);
		}
		buffer[0] = '\0';
	}
	buffer = ft_read_fd(fd, buffer);
	temp = buffer;
	line = ft_line(buffer);
	buffer = ft_buffer_update(buffer);
	free(temp);
	return (line);
}
