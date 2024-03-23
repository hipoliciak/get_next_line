/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:10:00 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/03/21 23:45:03 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	new_line_len(const char *file, unsigned int start)
{
	unsigned int	i;

	i = 0;
	if (file[start] == '\0')
		return (0);
	while (file[i + start] != '\n' && file[i + start] != '\0')
		i++;
	if (file[i + start] == '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*next;
	int				bytes_read;
	static char		*file;
	unsigned int	new_start;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bytes_read = 1;
	if (!file)
	{
		new_start = 0;
		file = ft_strdup("");
	}
	while (bytes_read != 0)
	{
		next = malloc(BUFFER_SIZE + 1);
		if (!next)
			return (0);
		bytes_read = read(fd, next, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		next[bytes_read] = '\0';
		file = ft_strjoin(file, next);
		if (ft_strchr(next, '\n'))
			break ;
		free(next);
	}
	line = ft_substr(file, new_start, new_line_len(file, new_start));
	if (new_line_len(file, new_start) == 0)
	{
		free (file);
		return (0);
	}
	new_start += ft_strlen(line);
	return (line);
}
