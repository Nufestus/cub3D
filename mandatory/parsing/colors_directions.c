/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:42 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/17 13:41:46 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	parse_colors(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		if (check_digits(str, &i, &count))
			return (1);
		if (check_count(str, &i, &count))
			return (1);
	}
	if (count != 3)
		return (1);
	return (0);
}

t_colors	handle_colors(char *str, t_cube *data)
{
	t_colors	rgb;
	int			len;
	char		*string;
	char		**colors;

	len = 2;
	while (str[len])
		len++;
	string = ft_substr(str, 2, len - 3);
	if (parse_colors(string))
	{
		free(string);
		free(str);
		gnl_free(data->map_fd);
		free_all(data);
		printf("Error\nColors Error\n");
		exit(1);
	}
	colors = ft_split(string, ',');
	rgb.r = ft_atoi(colors[0]);
	rgb.g = ft_atoi(colors[1]);
	rgb.b = ft_atoi(colors[2]);
	free_double_array(colors);
	free(string);
	return (rgb);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*handle_texture(char *str, t_cube *data)
{
	int		len;
	int		start;
	char	*copy;
	char	*texture_file;

	start = 3;
	while (str[start] && ft_isspace(str[start]))
		start++;
	len = start;
	while (str[len])
		len++;
	texture_file = ft_substr(str, start, len - 3);
	copy = texture_file;
	texture_file = ft_strtrim(texture_file, " \n");
	free(copy);
	if (!check_ext(texture_file))
	{
		printf("Error\nProblem in Textures\n");
		free(texture_file);
		free(str);
		gnl_free(data->map_fd);
		free_all(data);
		exit(1);
	}
	return (texture_file);
}

void	handle_directions(char *str, t_cube *data, int *count)
{
	if (!ft_strncmp(str, "NO ", 3) && !data->texture.north)
		data->texture.north = handle_texture(str, data);
	else if (!ft_strncmp(str, "SO ", 3) && !data->texture.south)
		data->texture.south = handle_texture(str, data);
	else if (!ft_strncmp(str, "WE ", 3) && !data->texture.west)
		data->texture.west = handle_texture(str, data);
	else if (!ft_strncmp(str, "EA ", 3) && !data->texture.east)
		data->texture.east = handle_texture(str, data);
	else if (!ft_strncmp(str, "F ", 2))
		data->texture.floor_color = handle_colors(str, data);
	else if (!ft_strncmp(str, "C ", 2))
		data->texture.sky_color = handle_colors(str, data);
	if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3)
		|| !ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
		(*count)++;
}
