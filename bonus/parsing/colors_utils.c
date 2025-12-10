/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:21:58 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/10 15:37:36 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_digits(char *str, int *i, int *count)
{
	int	num;
	int	digits_found;

	num = 0;
	digits_found = 0;
	while (str[(*i)] && ft_isdigit(str[(*i)]))
	{
		num = num * 10 + (str[(*i)] - '0');
		digits_found++;
		(*i)++;
	}
	if (digits_found == 0 || num > 255)
		return (1);
	(*count)++;
	return (0);
}

int	check_count(char *str, int *i, int *count)
{
	if ((*count) < 3)
	{
		if (str[(*i)] && str[(*i)] != ',')
			return (1);
		(*i)++;
	}
	else
	{
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		if (str[(*i)])
			return (1);
	}
	return (0);
}

int	check_ext(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i > 4)
	{
		str += i;
		str -= 4;
	}
	if (!ft_strcmp(str, ".xpm") && i > 4)
		return (1);
	return (0);
}
