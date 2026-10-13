/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:21:52 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/30 16:35:55 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_free(char *s)
{
	free(s);
	return (NULL);
}

static char	*read_until_newline(int fd, char *stash)
{
	size_t	len;
	size_t	cap;
	ssize_t	bytes;

	len = gnl_strlen(stash);
	cap = 0;
	if (gnl_strchr(stash, '\n') != NULL)
		return (stash);
	bytes = 1;
	while (bytes > 0)
	{
		stash = gnl_grow(stash, len, &cap);
		if (stash == NULL)
			return (NULL);
		bytes = read(fd, stash + len, BUFFER_SIZE);
		if (bytes < 0)
			return (gnl_free(stash));
		len += bytes;
		stash[len] = '\0';
		if (gnl_strchr(stash + len - bytes, '\n') != NULL)
			return (stash);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		stash = gnl_free(stash);
		return (NULL);
	}
	stash = read_until_newline(fd, stash);
	line = gnl_get_line(stash);
	if (line != NULL)
		stash = gnl_next_stash(stash);
	if (line == NULL)
		stash = gnl_free(stash);
	return (line);
}
