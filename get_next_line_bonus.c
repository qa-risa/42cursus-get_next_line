/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:39:50 by aiwane            #+#    #+#             */
/*   Updated: 2026/06/04 19:12:21 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_free(char *s)
{
	free(s);
	return (NULL);
}

static t_gnl_fd	*get_node(t_gnl_fd **nodes, int fd)
{
	t_gnl_fd	*cur;
	t_gnl_fd	*new;

	cur = *nodes;
	while (cur != NULL)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	new = malloc(sizeof(t_gnl_fd));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->stash = NULL;
	new->next = *nodes;
	*nodes = new;
	return (new);
}

static void	remove_node(t_gnl_fd **nodes, int fd)
{
	t_gnl_fd	*cur;
	t_gnl_fd	*prev;

	cur = *nodes;
	prev = NULL;
	while (cur != NULL)
	{
		if (cur->fd == fd)
		{
			if (prev == NULL)
				*nodes = cur->next;
			else
				prev->next = cur->next;
			free(cur->stash);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
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
	static t_gnl_fd	*nodes;
	t_gnl_fd		*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		remove_node(&nodes, fd);
		return (NULL);
	}
	node = get_node(&nodes, fd);
	if (node == NULL)
		return (NULL);
	node->stash = read_until_newline(fd, node->stash);
	line = gnl_get_line(node->stash);
	if (line != NULL)
		node->stash = gnl_next_stash(node->stash);
	if (line == NULL || node->stash == NULL)
		remove_node(&nodes, fd);
	return (line);
}
