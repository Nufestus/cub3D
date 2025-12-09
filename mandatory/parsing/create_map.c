/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:40:00 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 13:32:24 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	read_from_map(t_cube *data)
{
	int		count;
	int		linecount;
	char	*line;

	count = 0;
	linecount = 0;
	line = get_next_line(data->map_fd);
	while (line)
	{
		if (linecount >= 6 && count != 6)
			return (free(line), gnl_free(data->map_fd));
		if (count < 6)
			handle_directions(line, data, &count);
		else if (count == 6)
			newnode(line, &data->list_map);
		if (strcmp(line, "\n") && check_space(line))
			linecount++;
		free(line);
		line = get_next_line(data->map_fd);
	}
}

int	count_without_space(t_map **ptr)
{
	int		i;
	t_map	*copy;

	i = 0;
	while (*ptr)
	{
		if ((*ptr)->line[0] == '\n' && (*ptr)->line[1] == '\0')
			(*ptr) = (*ptr)->next;
		else
			break ;
	}
	copy = *ptr;
	while (copy)
	{
		if (copy->line[0] == '\n' && copy->line[1] == '\0')
			i++;
		else
			i = 0;
		copy = copy->next;
	}
	return (ft_lstsize(*ptr) - i);
}

void	make_map(t_cube *data)
{
	int		i;
	int		len;
	t_map	*ptr;

	i = 0;
	ptr = data->list_map;
	len = count_without_space(&ptr);
	if (!len)
		return ;
	data->map = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		data->map[i] = ft_strtrim(ptr->line, "\n");
		i++;
		ptr = ptr->next;
	}
	data->map[i] = NULL;
}

int	lengthcalc(size_t a, char *string)
{
	if (a > ft_strlen(string) - 1)
		return (1);
	return (0);
}
