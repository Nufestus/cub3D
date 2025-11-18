/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:42 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/18 13:55:29 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int parse_colors(char *str)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]) && str[i] != ',')
			return (1);
		if (str[i] == ',')
			check++;
		if (check > 2)
			return (1);
		i++;
	}
	return (0);
}

t_colors handle_colors(char *str, t_cube *data)
{
	t_colors rgb;
	int len;
	char *string;
	char **colors;

	(void)data;
	len = 2;
	while (str[len])
		len++;
	string = ft_substr(str, 2, len - 3);
	if (parse_colors(string))
		exit(120); // safe exit
	colors = ft_split(string, ',');
	rgb.r = ft_atoi(colors[0]);
	rgb.g = ft_atoi(colors[1]);
	rgb.b = ft_atoi(colors[2]);
	free_double_array(colors);
	free(string);
	return rgb;
}

int check_ext(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i > 4)
	{
		str += i;
		str -= 4;
	}
	if (!strcmp(str, ".xpm") && i > 4)
		return (1);
	return (0);
}

char *handle_texture(char *str)
{
	int len;
	int start;
	char *copy;
	char *texture_file;

	start = 3;
	while (str[start] && isspace(str[start]))
		start++;
	len = start;
	while (str[len])
		len++;
	texture_file = ft_substr(str, start, len - 3);
	copy = texture_file;
	texture_file = ft_strtrim(texture_file, " \n");
	free(copy);
	if (!check_ext(texture_file))
		return (NULL);
	return (texture_file);
}

void handle_directions(char *str, t_cube *data, int *count)
{
	if (!ft_strncmp(str, "NO ", 3))
		data->texture.north = handle_texture(str);
	else if (!ft_strncmp(str, "SO ", 3))
		data->texture.south = handle_texture(str);
	else if (!ft_strncmp(str, "WE ", 3))
		data->texture.west = handle_texture(str);
	else if (!ft_strncmp(str, "EA ", 3))
		data->texture.east = handle_texture(str);
	else if (!ft_strncmp(str, "F ", 2))
		data->texture.floor_color = handle_colors(str, data);
	else if (!ft_strncmp(str, "C ", 2))
		data->texture.sky_color = handle_colors(str, data);
    if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3)
        || !ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3)
        || !ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
        (*count)++;
}
