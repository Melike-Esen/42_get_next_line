/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meesen <meesen@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:43:03 by meesen            #+#    #+#             */
/*   Updated: 2025/08/28 18:23:51 by meesen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <unistd.h>

static char	*read_and_append(int fd, char *saved)
{
	char	*buffer;
	int		readed;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	readed = 1;
	while (!ft_strchr(saved, '\n') && readed != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buffer);
			free(saved);
			return (NULL);
		}
		buffer[readed] = '\0';
		saved = ft_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

static char	*get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*new_saved(char *saved)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new = malloc(ft_strlen(saved) - i);
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		new[j++] = saved[i++];
	new[j] = '\0';
	free(saved);
	return (new);
}

char *get_next_line(int fd)
{
    static char *saved;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    saved = read_and_append(fd, saved);
    if (!saved)
        return (NULL); // read sırasında hata olursa saved zaten free ediliyor
    line = get_line(saved);
    if (!line)
    {
        free(saved);  // line alınamadıysa saved'i de free et
        saved = NULL;
        return (NULL);
    }
    saved = new_saved(saved);
    return (line);
}
