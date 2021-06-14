/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:44:27 by ngregori          #+#    #+#             */
/*   Updated: 2021/05/19 20:08:59 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	read_file(int fd, char **arr, char *buffer)
{
	ssize_t	read_bytes;
	char	*tmp;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0)
		return (ERR);
	if (read_bytes == 0)
		return (EOFILE);
	buffer[read_bytes] = '\0';
	if (arr[fd] == NULL)
		arr[fd] = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(arr[fd], buffer);
		free(arr[fd]);
		arr[fd] = tmp;
	}
	if (arr[fd] == NULL)
		return (ERR);
	return (OK);
}

static	int	update_line(int fd, char **arr, char **line)
{
	char	*index;
	char	*tmp;

	index = ft_strchr(arr[fd], '\n');
	if (index)
	{
		*line = ft_substr(arr[fd], 0, index - arr[fd]);
		tmp = ft_substr(index, 1, ft_strlen(arr[fd]) - (index - arr[fd] + 1));
		free(arr[fd]);
		arr[fd] = tmp;
		return (OK);
	}
	else
	{
		if (arr[fd])
		{
			*line = ft_strdup(arr[fd]);
			free(arr[fd]);
			arr[fd] = NULL;
		}
		else
			*line = ft_strdup("\0");
	}
	return (EOFILE);
}

int	get_next_line(int fd, char **line)
{
	static char	*arr[MAX_FD];
	int			status;
	char		*buffer;

	status = 1;
	if (line == NULL || BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (ERR);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ERR);
	while (!ft_strchr(arr[fd], '\n') && status > 0)
		status = read_file(fd, arr, buffer);
	free(buffer);
	if (status == ERR)
		return (ERR);
	else
		status = update_line(fd, arr, line);
	return (status);
}
