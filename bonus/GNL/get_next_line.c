/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:06:05 by aammisse          #+#    #+#             */
/*   Updated: 2024/11/25 00:02:32 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

char	*read_file(int fd, char *str)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = (char *)ft_calloc((size_t)BUFFER_SIZE + 1, 1);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*read_line(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*str || !str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	new_str = (char *)ft_calloc(i + 1, 1);
	while (j < i)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*reset_oldstr(char *str)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	newstr = (char *)ft_calloc(((ft_strlen(str) - i) + 1), 1);
	i++;
	while (str[i] != '\0')
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = read_file(fd, str);
	if (!str)
		return (NULL);
	line = read_line(str);
	str = reset_oldstr(str);
	return (line);
}
