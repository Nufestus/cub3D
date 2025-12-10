/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:07:32 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/09 15:10:36 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_doors(t_cube *data)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
				res++;
			j++;
		}
		i++;
	}
	return (res);
}

void	assign_doors(t_cube *data)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
			{
				data->doors[index].open = 0;
				data->doors[index].x = j;
				data->doors[index].y = i;
				data->doors[index].count = count_doors(data);
				index++;
			}
			j++;
		}
		i++;
	}
}

void	create_doors(t_cube *data)
{
	int	doors;

	doors = count_doors(data);
	data->doors = malloc(sizeof(t_door) * doors);
	if (!data->doors)
	{
		destroy_all(data);
		exit(1);
	}
	assign_doors(data);
}
