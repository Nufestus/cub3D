/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:04:23 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:42:13 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_sprite(t_cube *data)
{
	t_sprite	sprite;

	sprite.image = &data->texture.sprite.torch
	[data->texture.sprite.current_frame];
	sprite.start = (WIDTH * 0.7) - (sprite.image->img_width / 2);
	sprite.end = (HEIGHT - sprite.image->img_height) + 75;
	sprite.y = 0;
	while (sprite.y < sprite.image->img_height)
	{
		sprite.x = 0;
		while (sprite.x < sprite.image->img_width)
		{
			draw_pixel(data, &sprite);
			sprite.x++;
		}
		sprite.y++;
	}
}

void	sprite_animation(t_cube *data)
{
	data->texture.sprite.timer++;
	if (data->anime == 1 && data->texture.sprite.timer >= 4)
	{
		data->texture.sprite.timer = 0;
		data->texture.sprite.current_frame++;
		if (data->texture.sprite.current_frame > 7)
		{
			data->texture.sprite.current_frame = 0;
			data->anime = 0;
		}
	}
}

int	create_rgb(t_colors *color)
{
	return ((color->r << 16) | (color->g << 8) | (color->b));
}
