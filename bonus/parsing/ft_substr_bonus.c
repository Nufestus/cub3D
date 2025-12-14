/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:39:18 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 14:02:21 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*substr;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	str = (char *)s;
	if (start > i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	lengthcalc(size_t a, char *string)
{
	if (a > ft_strlen(string) - 1)
		return (1);
	return (0);
}

void	destroy_all(t_cube *data)
{
	int	i;

	i = 0;
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_n);
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_s);
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_e);
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_w);
	safe_destroy(data->mlxstruct.mlx, &data->texture.door);
	safe_destroy(data->mlxstruct.mlx, &data->mlxstruct.img);
	while (i < 8)
		safe_destroy(data->mlxstruct.mlx, &data->texture.sprite.torch[i++]);
	if (data->mlxstruct.win)
		mlx_destroy_window(data->mlxstruct.mlx, data->mlxstruct.win);
	if (data->mlxstruct.mlx)
		mlx_destroy_display(data->mlxstruct.mlx);
	free_all(data);
	free(data->mlxstruct.mlx);
	exit(0);
}

int	*make_array(t_cube *data)
{
	int	i;
	int	*array;

	i = 0;
	while (data->map[i])
		i++;
	array = malloc(sizeof(int) * i);
	if (!array)
		free_all(data);
	return (array);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
