/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:39:18 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/18 13:53:05 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t i;
	char *str;
	char *substr;

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

void free_double_array(char **s)
{
	char **l = s;

	while (*s)
	{
		free(*s);
		s++;
	}
	free(l);
}