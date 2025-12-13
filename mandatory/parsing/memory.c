/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 08:26:18 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/10 15:39:46 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_lst(t_map *head)
{
	t_map	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

void	free_textures(t_cube *data)
{
	if (data->texture.north)
		free(data->texture.north);
	if (data->texture.south)
		free(data->texture.south);
	if (data->texture.east)
		free(data->texture.east);
	if (data->texture.west)
		free(data->texture.west);
}

void	free_double_array(char **s)
{
	char	**l;

	if (!s || !(*s))
		return ;
	l = s;
	while (*s)
	{
		free(*s);
		s++;
	}
	free(l);
}

void	free_all(t_cube *data)
{
	if (data->dimensions)
		free(data->dimensions);
	if (data->map_file)
		free(data->map_file);
	close(data->map_fd);
	if (data->list_map)
		free_lst(data->list_map);
	free_double_array(data->map);
	free_textures(data);
}

void	gnl_free(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
