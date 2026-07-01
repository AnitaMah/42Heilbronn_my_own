/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 15:31:44 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/23 15:34:09 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	save_rest(char *line, char *leftover)
{
	char	*nl;
	size_t	i;

	i = 0;
	if (!line)
	{
		leftover[0] = '\0';
		return ;
	}
	nl = ft_strchr(line, '\n');
	if (!nl || !*(nl + 1))
	{
		leftover[0] = '\0';
		return ;
	}
	nl++;
	while (*nl && i < BUFFER_SIZE)
		leftover[i++] = *nl++;
	leftover[i] = '\0';
}

char	*extract_line(char *line)
{
	char	*nl;

	if (!line || !*line)
		return (NULL);
	nl = ft_strchr(line, '\n');
	if (nl)
		return (ft_substr(line, 0, (nl - line) + 1));
	return (ft_strdup(line));
}

char	*append_buf(char *line, char *buf, ssize_t n)
{
	char	*tmp;
	size_t	len;

	if (!line)
		line = ft_strdup("");
	len = ft_strlen(line);
	tmp = malloc(len + n + 1);
	if (!tmp)
		return (free(line), NULL);
	ft_memcpy(tmp, line, len);
	ft_memcpy(tmp + len, buf, n);
	tmp[len + n] = '\0';
	free(line);
	return (tmp);
}

char	*read_from_file(int fd, char *line)
{
	char	*buf;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (free(line), NULL);
	while (!ft_strchr(line, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == 0)
			break ;
		if (n < 0)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		line = append_buf(line, buf, n);
		if (!line)
			return (free(buf), NULL);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	leftover[BUFFER_SIZE + 1];
	char		*line;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup(leftover);
	if (!line)
	{
		leftover[0] = '\0';
		return (NULL);
	}
	line = read_from_file(fd, line);
	if (!line)
	{
		leftover[0] = '\0';
		return (NULL);
	}
	res = extract_line(line);
	save_rest(line, leftover);
	free(line);
	if (!res)
		leftover[0] = '\0';
	return (res);
}
