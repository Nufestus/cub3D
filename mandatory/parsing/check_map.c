/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:38:33 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/22 16:04:06 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int check_newline(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int check_top_bot(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '0' || strchr("NSEW", map[0][i]))
			return (1);
		i++;
	}
	i = 0;
	while (map[i])
		i++;
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '0' || strchr("NSEW", map[i][j]))
			return (1);
		j++;
	}
	return (0);
}

int check_edges(char **map)
{
	int i;

	if (check_top_bot(map))
		return (1);
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '0' || map[i][ft_strlen(map[i]) - 1] == '0' || strchr("NSEW", map[i][0]) || strchr("NSEW", map[i][ft_strlen(map[i]) - 1]))
			return (1);
		i++;
	}
	return (0);
}

int lengthcalc(size_t a, char *string)
{
	if (a > ft_strlen(string) - 1)
		return 1;
	return (0);
}

void set_player(t_cube *data, int i, int j, char **map)
{
	data->pixely = calculate_pixel(i) + (TILE_SIZE / 2);
	data->pixelx = calculate_pixel(j) + (TILE_SIZE / 2);
	data->player.x = data->pixelx / (double)TILE_SIZE;
	data->player.y = data->pixely / (double)TILE_SIZE;
	if (map[i][j] == 'N')
	{
		data->player.dirX = 0;
		data->player.dirY = -1;
		data->player.planeX = 0.66;
		data->player.planeY = 0;
	}
	else if (map[i][j] == 'S')
	{
		data->player.dirX = 0;
		data->player.dirY = 1;
		data->player.planeX = -0.66;
		data->player.planeY = 0;
	}
	else if (map[i][j] == 'E')
	{
		data->player.dirX = 1;
		data->player.dirY = 0;
		data->player.planeX = 0;
		data->player.planeY = 0.66;
	}
	else if (map[i][j] == 'W')
	{
		data->player.dirX = -1;
		data->player.dirY = 0;
		data->player.planeX = 0;
		data->player.planeY = -0.66;
	}
	map[i][j] = '0';
}

int check_middle(char **map, t_cube *data)
{
	size_t i;
	size_t j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || strchr("NSEW", map[i][j])) && ((map[i][j + 1] && map[i][j + 1] == ' ') || (j > 0 && map[i][j - 1] && map[i][j - 1] == ' ')))
				return (1);
			else if ((map[i][j] == '0' || strchr("NSEW", map[i][j])) && (((lengthcalc(j, map[i + 1])) || (i > 0 && lengthcalc(j, map[i - 1]))) || (i > 0 && map[i - 1][j] == ' ') || (map[i + 1] && map[i + 1][j] == ' ')))
				return (1);
			if (strchr("NSEW", map[i][j]))
                set_player(data, i, j, map);
			j++;
		}
		i++;
	}
	return (0);
}
