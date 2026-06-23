/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 11:17:31 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/23 12:55:24 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	save_rest(char *line, char *leftover)
{
	char	*newline_ptr;
	int		i;
	int		j;

	newline_ptr = ft_strchr(line, '\n');
	if (!newline_ptr)
	{
		leftover[0] = '\0';
		return ;
	}
	i = (newline_ptr - line) + 1;
	j = 0;
	while (line[i + j])
	{
		leftover[j] = line[i + j];
		j++;
	}
	leftover[j] = '\0';
}

char	*extract_line(char *line)
{
	char	*newline;
	char	*res;

	newline = ft_strchr(line, '\n');
	if (!newline)
		return (line);
	res = ft_substr(line, 0, (newline - line) + 1);
	free(line);
	return (res);
}

char	*read_from_file(int fd, char *line)
{
	char	*buf;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(line), NULL);
	n = 1;
	while (!ft_strchr(line, '\n') && n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (free(buf), free(line), NULL);
		if (n == 0)
			break ;
		buf[n] = '\0';
		line = ft_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	leftover[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup(leftover);
	line = read_from_file(fd, line);
	if (!line || *line == '\0')
	{
		free(line);
		leftover[0] = '\0';
		return (NULL);
	}
	save_rest(line, leftover);
	return (extract_line(line));
}
