/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 16:28:00 by aiwane            #+#    #+#             */
/*   Updated: 2026/05/30 16:35:53 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*gnl_grow(char *stash, size_t len, size_t *cap)
{
	char	*new_stash;
	size_t	i;

	if (*cap >= len + BUFFER_SIZE + 1)
		return (stash);
	*cap = (len + BUFFER_SIZE + 1) * 2;
	new_stash = malloc(*cap);
	if (new_stash == NULL)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_stash[i] = stash[i];
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*gnl_get_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	len = 0;
	while (stash[len] != '\0' && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*gnl_next_stash(char *stash)
{
	char	*next;
	size_t	i;
	size_t	j;

	next = NULL;
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (stash[i] != '\0')
		next = malloc(gnl_strlen(stash) - i + 1);
	if (next != NULL)
	{
		j = 0;
		while (stash[i] != '\0')
			next[j++] = stash[i++];
		next[j] = '\0';
	}
	free(stash);
	return (next);
}
