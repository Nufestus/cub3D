/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:14:46 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/30 15:21:34 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int is_door_closed(t_cube *data, double x, double y)
{
    t_door *door = get_units(data, (int)x, (int)y);
    if (door->open == 0)
        return (1);
    return (0);
}

int is_wall(t_cube *data, double x, double y)
{
    if (data->map[(int)y][(int)x] == '1' || (data->map[(int)y][(int)x] == 'D' && is_door_closed(data, x, y)))
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
    if (is_wall(data, x - r, y - r)) return 1;
    if (is_wall(data, x + r, y + r)) return 1;
    if (is_wall(data, x + r, y - r)) return 1;
    if (is_wall(data, x - r, y + r)) return 1;

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
    data->ray.side = 0;
    data->ray.door = 0;
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

int is_closed(t_cube *data)
{
    t_door *door;

    door = get_units(data, data->ray.mapX, data->ray.mapY);
    if (door->open == 0)
        return (1);
    return (0);
}

void dda(t_cube *data)
{
    while (data->ray.hit == 0 && data->ray.door == 0)
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
        else if (data->map[data->ray.mapY][data->ray.mapX] == 'D' && is_closed(data))
            data->ray.door = 1;
    }
}

int create_rgb(t_colors *color)
{
    return ((color->r << 16) | (color->g << 8) | (color->b));
}

void draw_line(int x, t_cube *data)
{
    t_img   *tex;
    int     tex_x;
    int     tex_y;
    double  step;
    double  tex_pos;
    int drawstart;
    int drawend;
    int  lineheight;
    int y;


    get_tex_info(data, &tex, &tex_x);
    lineheight = HEIGHT / data->ray.perpWallDist;
    
    step = ((double)tex->img_height / (double)lineheight);
    drawstart = -lineheight / 2 + HEIGHT / 2;
    if (drawstart < 0)
        drawstart = 0;
    drawend = lineheight / 2 + HEIGHT / 2;
    if (drawend >= HEIGHT)
        drawend = HEIGHT - 1;
    tex_pos = (drawstart - HEIGHT / 2 + lineheight / 2) * step;
    y = 0;
    while (y < HEIGHT)
    {
        if (y >= 0 && y < drawstart)
            my_mlx_pixel_put(&data->mlxstruct, x, y, create_rgb(&data->texture.sky_color));
        else if (y >= drawstart && y < drawend)
        {
            tex_y = (int)tex_pos % tex->img_height;
            tex_pos += step;
            my_mlx_pixel_put(&data->mlxstruct, x, y, get_pixel_color(tex, tex_x, tex_y));
        }
        else
            my_mlx_pixel_put(&data->mlxstruct, x, y, create_rgb(&data->texture.floor_color));
        y++;
    }
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
    cast_rays(data);
    mlx_put_image_to_window(data->mlxstruct.mlx, data->mlxstruct.win,
                            data->mlxstruct.img.img, 0, 0);
}