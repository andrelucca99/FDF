/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:53:22 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/06 16:43:18 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_end_of_line(int fd, char *buffer)
{
	int		read_file;
	char	*temp;
	char	*new_buffer;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_file = 1;
	while (read_file > 0)
	{
		read_file = read(fd, temp, BUFFER_SIZE);
		if (read_file < 0)
			return (free(buffer), free(temp), NULL);
		temp[read_file] = 0;
		new_buffer = ft_strjoin(buffer, temp);
		free(buffer);
		buffer = new_buffer;
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	if (read_file == 0 && (!buffer || buffer[0] == '\0'))
		return (free(buffer), NULL);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*temp;
	int		i;

	if (!buffer)
		return (NULL);
	temp = ft_calloc(ft_strlen(buffer) + 1, sizeof(char));
	if (!temp)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		temp[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		temp[i] = '\n';
	return (temp);
}

static char	*get_buffer_update(char *buffer)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	temp = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!temp)
		return (free(buffer), NULL);
	i += 1;
	j = 0;
	while (buffer[i])
		temp[j++] = buffer[i++];
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_end_of_line(fd, buffer);
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	line = get_line(buffer);
	if (!line || line[0] == '\0')
		return (free(buffer), free(line), NULL);
	buffer = get_buffer_update(buffer);
	return (line);
}
