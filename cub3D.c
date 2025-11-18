/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:58:26 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/18 17:13:39 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cube	data;

	if (ac != 2)
	{
		write(2, "Invalid File Map!\n", 19);
		return (1);
	}
	// initialize to null
	data.map_file = ft_strdup(av[1]);
	data.map_fd = openmap(av[1]);
	data.list_map = NULL;
	data.map = NULL;
	read_from_map(&data);
	create_map(&data);
	// open files
	printmap(&data);
	render_map(&data.mlxstruct, &data);
}
