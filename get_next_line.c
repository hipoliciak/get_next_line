/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:10:00 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/03/20 21:47:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	new_line_len(const char *file, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (file[i + start] != '\n' && file[i + start] != '\0')
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

	new_start = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!file)
		file = ft_strdup("");
	else
		new_start = new_line_len(file, new_start);
	bytes_read = 1;
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
		free(next);
	}
	line = ft_substr(file, new_start, new_line_len(file, new_start));
	return (line);
}
