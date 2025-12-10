/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:39:18 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/10 15:21:53 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_player(t_cube *data, int x, int y)
{
	if (x == (int)data->player.x && y == (int)data->player.y)
		return (1);
	return (0);
}

int	is_next_door(t_cube *data)
{
	if (data->map[(int)data->player.y + 1][(int)data->player.x] == 'D'
		|| data->map[(int)data->player.y - 1][(int)data->player.x] == 'D'
		|| data->map[(int)data->player.y][(int)data->player.x + 1] == 'D'
		|| data->map[(int)data->player.y][(int)data->player.x - 1] == 'D')
		return (1);
	return (0);
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
