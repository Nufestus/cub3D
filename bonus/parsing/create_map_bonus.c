/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:40:00 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/17 13:55:40 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
			newnode(data, line, &data->list_map);
		if (ft_strcmp(line, "\n") && check_space(line))
			linecount++;
		free(line);
		line = get_next_line(data->map_fd);
	}
}

int	count_without_space(t_map **ptr)
{
	int		flag;
	t_map	*copy;

	flag = 0;
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
		if (flag == 1 && copy->line[0] != '\n')
			return (0);
		if (copy->line[0] == '\n' && copy->line[1] == '\0')
			flag = 1;
		copy = copy->next;
	}
	return (ft_lstsize(*ptr));
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
