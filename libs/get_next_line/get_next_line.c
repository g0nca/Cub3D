/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:15:02 by ggomes-v          #+#    #+#             */
/*   Updated: 2024/11/20 13:16:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*newline(char *str)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	newline = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!newline)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		newline[j++] = str[i++];
	newline[j] = '\0';
	free(str);
	return (newline);
}

char	*extract_line(char *str)
{
	int		i;
	char		*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *str)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(str, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		str = ft_strjoin(str, buffer);
		//if (ft_strchr(str, '\n'))
			//break;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	line = extract_line(str);
	if (!line)
		return (NULL);
	str = newline(str);
	return (line);
}

int main(void)
{
    int i;
    char *line;

    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        write(1, "\nErro ao Abrir o Ficheiro\n", 1);
        return (0);
    }
    i = 0;
    line = get_next_line(0);
    while (line != 0)
    {
        printf("LINE[%d]:%s", i, line);
        free(line);
        line = get_next_line(0);
        i++;
    }
    close(fd);
    return (0);
}