/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:14:46 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/24 17:12:48 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int is_wall(t_cube *data, double x, double y)
{
    if (data->map[(int)y][(int)x] == '1')
        return (1);
    return (0);
}

int collides(t_cube *data, double x, double y)
{
    double r = HITBOX;

    if (is_wall(data, x + r, y)) return 1;
    if (is_wall(data, x - r, y)) return 1;
    if (is_wall(data, x, y + r)) return 1;
    if (is_wall(data, x, y - r)) return 1;

    return 0;
}

void update_player(t_cube *data)
{
    double newX;
    double newY;

    /* ---------- FORWARD ---------- */
    if (data->player.move_direction_front == 1)
    {
        newX = data->player.x + data->player.dirX * PLR_SPEED;
        if (!collides(data, newX, data->player.y))
            data->player.x = newX;

        newY = data->player.y + data->player.dirY * PLR_SPEED;
        if (!collides(data, data->player.x, newY))
            data->player.y = newY;
    }

    /* ---------- BACKWARD ---------- */
    if (data->player.move_direction_front == -1)
    {
        newX = data->player.x - data->player.dirX * PLR_SPEED;
        if (!collides(data, newX, data->player.y))
            data->player.x = newX;

        newY = data->player.y - data->player.dirY * PLR_SPEED;
        if (!collides(data, data->player.x, newY))
            data->player.y = newY;
    }

    /* ---------- STRAFE RIGHT ---------- */
    if (data->player.move_direction_side == 1)
    {
        newX = data->player.x + data->player.dirY * PLR_SPEED;
        if (!collides(data, newX, data->player.y))
            data->player.x = newX;

        newY = data->player.y - data->player.dirX * PLR_SPEED;
        if (!collides(data, data->player.x, newY))
            data->player.y = newY;
    }

    /* ---------- STRAFE LEFT ---------- */
    if (data->player.move_direction_side == -1)
    {
        newX = data->player.x - data->player.dirY * PLR_SPEED;
        if (!collides(data, newX, data->player.y))
            data->player.x = newX;

        newY = data->player.y + data->player.dirX * PLR_SPEED;
        if (!collides(data, data->player.x, newY))
            data->player.y = newY;
    }

    /* ---------- TURN LEFT ---------- */
    if (data->player.turn_direction == -1)
    {
        double rot = -PLR_ROTATE;
        double oldDirX = data->player.dirX;
        double oldPlaneX = data->player.planeX;

        data->player.dirX = data->player.dirX * cos(rot) - data->player.dirY * sin(rot);
        data->player.dirY = oldDirX * sin(rot) + data->player.dirY * cos(rot);

        data->player.planeX = data->player.planeX * cos(rot) - data->player.planeY * sin(rot);
        data->player.planeY = oldPlaneX * sin(rot) + data->player.planeY * cos(rot);
    }

    /* ---------- TURN RIGHT ---------- */
    if (data->player.turn_direction == 1)
    {
        double rot = PLR_ROTATE;
        double oldDirX = data->player.dirX;
        double oldPlaneX = data->player.planeX;

        data->player.dirX = data->player.dirX * cos(rot) - data->player.dirY * sin(rot);
        data->player.dirY = oldDirX * sin(rot) + data->player.dirY * cos(rot);

        data->player.planeX = data->player.planeX * cos(rot) - data->player.planeY * sin(rot);
        data->player.planeY = oldPlaneX * sin(rot) + data->player.planeY * cos(rot);
    }
}

void draw_sky_floor(t_cube *data)
{
    int x;
    int y;
    
    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(&data->mlxstruct, x, y, SKYCOLOR);
            x++;
        }
        y++;
    }
    y = HEIGHT / 2;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(&data->mlxstruct, x, y, FLOORCOLOR);
            x++;
        }
        y++;
    }
}

void initialize_values(int x, t_cube *data)
{
    double cameraX;
    
    cameraX = 2.0 * x / (double)WIDTH - 1.0;
    data->ray.rayDirX = data->player.dirX + data->player.planeX * cameraX;
    data->ray.rayDirY = data->player.dirY + data->player.planeY * cameraX;
    data->ray.mapX = (int)data->player.x;
    data->ray.mapY = (int)data->player.y;
    data->ray.deltaDistX = fabs(1 / data->ray.rayDirX);
    data->ray.deltaDistY = fabs(1 / data->ray.rayDirY);
    data->ray.hit = 0;
}

void calculate_step(t_cube *data)
{
    if (data->ray.rayDirX < 0)
    {
        data->ray.stepX = -1;
        data->ray.sideDistX = (data->player.x - data->ray.mapX) * data->ray.deltaDistX;
    }
    else if (data->ray.rayDirX > 0)
    {
        data->ray.stepX = 1;
        data->ray.sideDistX = (data->ray.mapX + 1.0 - data->player.x) * data->ray.deltaDistX;
    }
    if (data->ray.rayDirY < 0)
    {
        data->ray.stepY = -1;
        data->ray.sideDistY = (data->player.y - data->ray.mapY) * data->ray.deltaDistY;
    }
    else if (data->ray.rayDirY > 0)
    {
        data->ray.stepY = 1;
        data->ray.sideDistY = (data->ray.mapY + 1.0 - data->player.y) * data->ray.deltaDistY;
    }
}

void dda(t_cube *data)
{
    data->ray.deltaDistX = (data->ray.rayDirX == 0.0) ? 1e30 : fabs(1.0 / data->ray.rayDirX);
    data->ray.deltaDistY = (data->ray.rayDirY == 0.0) ? 1e30 : fabs(1.0 / data->ray.rayDirY);
    while (data->ray.hit == 0)
    {
        if (data->ray.sideDistX < data->ray.sideDistY)
        {
            data->ray.mapX += data->ray.stepX;
            data->ray.sideDistX += data->ray.deltaDistX;
            data->ray.side = 0;
        }
        else
        {
            data->ray.mapY += data->ray.stepY;
            data->ray.sideDistY += data->ray.deltaDistY;
            data->ray.side = 1;
        }
        if (data->map[data->ray.mapY][data->ray.mapX] == '1')
            data->ray.hit = 1;
    }
}

void draw_line(int x, t_cube *data)
{
    int drawstart;
    int drawend;
    int lineheight;
    int color;

    lineheight = HEIGHT / data->ray.perpWallDist;
    drawstart = -lineheight / 2 + HEIGHT / 2;
    if (drawstart < 0)
        drawstart = 0;
    drawend = lineheight / 2 + HEIGHT / 2;
    if (drawend >= HEIGHT)
        drawend = HEIGHT - 1;
    if (data->ray.side == 0)
        color = 0x00008B;
    else
        color = 0x0000FF;
    for (int y = drawstart; y < drawend; y++)
        my_mlx_pixel_put(&data->mlxstruct, x, y, color);
}

void cast_rays(t_cube *data)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        initialize_values(x, data);
        calculate_step(data);
        dda(data);
        if (data->ray.side == 0)
            data->ray.perpWallDist = data->ray.sideDistX - data->ray.deltaDistX;
        else
            data->ray.perpWallDist = data->ray.sideDistY - data->ray.deltaDistY;
        draw_line(x, data);
        x++;
    }
}

void render_frame(t_cube *data)
{
    draw_sky_floor(data);
    cast_rays(data);
    mlx_put_image_to_window(data->mlxstruct.mlx, data->mlxstruct.win,
                            data->mlxstruct.img.img, 0, 0);
}