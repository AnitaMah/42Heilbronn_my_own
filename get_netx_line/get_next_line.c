/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmakhov <anmakhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:11:43 by anmakhov          #+#    #+#             */
/*   Updated: 2026/06/02 14:10:46 by anmakhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_stash(char *stash)
{
	char	*new;
	size_t	iter;
	size_t	second_iter;

	if (!stash)
		return (NULL);
	iter = 0;
	while (stash[iter] && stash[iter] != '\n')
		iter++;
	if (!stash[iter])
		return (free(stash), NULL);
	iter++;
	new = malloc(ft_strlen(stash + iter) + 1);
	if (!new)
		return (free(stash), NULL);
	second_iter = 0;
	while (stash[iter])
		new[second_iter++] = stash[iter++];
	new[second_iter] = '\0';
	free(stash);
	return (new);
}

char	*extract_line(char *stash)
{
	char	*nl;
	char	*line;
	size_t	len;
	size_t	iter;

	if (!stash)
		return (NULL);
	nl = ft_strchr(stash, '\n');
	if (nl)
		len = (size_t)(nl - stash + 1);
	else
		len = ft_strlen(stash);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	iter = 0;
	while (iter < len)
	{
		line[iter] = stash[iter];
		iter++;
	}
	line[len] = '\0';
	return (line);
}

char	*read_to_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes;
	char	*tmp;

	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (free(stash), NULL);
		free(stash);
		stash = tmp;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd] || !ft_strchr(stash[fd], '\n'))
		stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd] || !stash[fd][0])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = extract_line(stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
