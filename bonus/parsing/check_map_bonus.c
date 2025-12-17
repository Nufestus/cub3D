/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:38:33 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/17 14:11:43 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	check_newline(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	check_top_bot(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i])
	{
		if (!ft_strchr("1 	", map[0][i]))
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
		if (!ft_strchr("1 	", map[i][j]))
			return (1);
		j++;
	}
	return (0);
}

int	check_edges(char **map)
{
	int	i;

	if (check_top_bot(map))
		return (1);
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\0')
		{
			i++;
			continue ;
		}
		else if (!ft_strchr("1 	", map[i][0]) ||
			!ft_strchr("1 	", map[i][ft_strlen(map[i]) - 1]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_cells(char **map, t_cube *data, size_t i, size_t j)
{
	if (!ft_strchr("01NSEWD 	", map[i][j]))
		return (1);
	if ((map[i][j] == '0' || ft_strchr("NSEWD", map[i][j])) &&
		((map[i][j + 1] && map[i][j + 1] == ' ') ||
		(j > 0 && map[i][j - 1] && map[i][j - 1] == ' ')))
		return (1);
	else if ((map[i][j] == '0' || ft_strchr("NSEWD", map[i][j])) &&
		(((lengthcalc(j, map[i + 1])) ||
		(i > 0 && lengthcalc(j, map[i - 1]))) ||
		(i > 0 && map[i - 1][j] == ' ') ||
		(map[i + 1] && map[i + 1][j] == ' ')))
		return (1);
	if (ft_strchr("NSEW", map[i][j]))
		set_player(data, i, j, map);
	return (0);
}

int	check_middle(char **map, t_cube *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_cells(map, data, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
