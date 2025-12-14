/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:40:31 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:30:05 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	openmap(t_cube *data)
{
	int	fd;

	fd = open(data->map_file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Unable to Open file!\n", 22);
		free(data->map_file);
		exit(1);
	}
	return (fd);
}

void	check_player(char **map, t_cube *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count > 1 || !count)
	{
		printf("Error\nMissing or Multiple Player(s)\n");
		free_all(data);
		exit(1);
	}
}

int	parse_map(t_cube *data)
{
	if (!data->map)
		return (1);
	if (check_newline(data->map))
		return (1);
	check_player(data->map, data);
	if (check_edges(data->map))
		return (1);
	if (check_middle(data->map, data))
		return (1);
	return (0);
}

void	create_map(t_cube *data)
{
	make_map(data);
	if (parse_map(data))
	{
		printf("Error\nInvalid Map\n");
		free_all(data);
		exit(1);
	}
}
