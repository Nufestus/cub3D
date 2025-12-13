/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:14:46 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/13 14:23:28 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	cast_rays(t_cube *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		initialize_values(x, data);
		calculate_step(data);
		dda(data);
		if (data->ray.side == 0)
		{
			data->ray.perpwalldist = data->ray.sidedist_x
				- data->ray.deltadist_x;
		}
		else
		{
			data->ray.perpwalldist = data->ray.sidedist_y
				- data->ray.deltadist_y;
		}
		draw_line(x, data);
		x++;
	}
}
