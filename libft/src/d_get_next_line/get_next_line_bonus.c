/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:47:26 by azubieta          #+#    #+#             */
/*   Updated: 2024/11/22 21:30:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_buffer_update_bonus(char *buffer)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (ft_free(buffer));
	ptr = malloc(((ft_strlen(buffer) - i) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		ptr[j++] = buffer[i++];
	ptr[j] = '\0';
	free(buffer);
	return (ptr);
}

char	*ft_read_fd_bonus(int fd, char *buffer)
{
	char	*ptr;
	char	*temp;
	int		bytes;

	bytes = 1;
	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && bytes != 0)
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

char	*get_next_line_bonus(int fd)
{
	static t_list	*list;
	t_list			*current;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	current = list;
	while (current && current->fd != fd)
		current = current->next;
	if (!current)
	{
		current = ft_newnode(fd);
		if (!current)
			return (NULL);
		current->next = list;
		list = current;
	}
	current->buffer = ft_read_fd(fd, current->buffer);
	if (!current->buffer)
		return (ft_freenode(&list, fd));
	line = ft_line(current->buffer);
	current->buffer = ft_buffer_update(current->buffer);
	if (!current->buffer)
		ft_freenode(&list, fd);
	return (line);
}

/*
int main(int argc, char *argv[])
{
    int     fd;
    int     fd_2;
    char    *line;
    char    *line_2;
    int     num_lines = 7;
    int     num_lines_2 = 7;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("%d\n", fd);
        write(1, "Error File\n", 11);
		return (0);
    }
    while (num_lines)
    {
        line = get_next_line(fd);
        printf("Linea_%d: %s\n", 8 - num_lines, line);
		free(line);
        num_lines--;
    }
	close(fd);
    fd_2 = open(argv[2], O_RDONLY);
    if (fd_2 == -1)
    {
        printf("%d\n", fd_2);
        write(1, "Error File\n", 11);
		return (0);
    }
    while (num_lines_2)
    {
        line_2 = get_next_line(fd_2);
        printf("Linea_%d: %s\n", 8 - num_lines_2, line_2);
		free(line_2);
        num_lines_2--;
    }
	close(fd_2);
    return (0);
}*/
/* así era al principio sin los frees:
char	*get_next_line(int fd)
{
	t_list	*list;   
    char			*line;
    
    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    if (list == NULL)
        list = ft_newnode(fd);
    if (list != NULL)
    {
        while (list->fd != fd && list->next != NULL)
            list = list->next;
        if (list->next == NULL && list->fd != fd)
        {
            list->next = ft_newnode(fd);
            list = list->next;
        }
    }
    list->buffer = ft_read_fd(fd, list->buffer);
    if (!list->buffer)
	{
		//meter frees
        return (NULL);
	}
    line = ft_line(list->buffer);
    list->buffer = ft_buffer_update(list->buffer);
    return (line);
}
*/