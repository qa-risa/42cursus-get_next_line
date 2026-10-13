/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwane <aiwane@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:40:16 by aiwane            #+#    #+#             */
/*   Updated: 2026/06/09 14:26:12 by aiwane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl_fd
{
	int				fd;
	char			*stash;
	struct s_gnl_fd	*next;
}					t_gnl_fd;

char				*get_next_line(int fd);
size_t				gnl_strlen(char *s);
char				*gnl_strchr(char *s, int c);
char				*gnl_grow(char *stash, size_t len, size_t *cap);
char				*gnl_get_line(char *stash);
char				*gnl_next_stash(char *stash);

#endif
