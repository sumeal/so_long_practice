/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:05:50 by muzz              #+#    #+#             */
/*   Updated: 2025/01/17 10:06:43 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_textures(t_data *data)
{
	int	img_width;
	int	img_height;

	data->wall = mlx_xpm_file_to_image(data->mlx, "wall.xpm", &img_width, &img_height);
	data->collectible = mlx_xpm_file_to_image(data->mlx, "collectible.xpm", &img_width, &img_height);
	data->exit = mlx_xpm_file_to_image(data->mlx, "exit.xpm", &img_width, &img_height);
	data->player = mlx_xpm_file_to_image(data->mlx, "player.xpm", &img_width, &img_height);

	if (!data->wall || !data->collectible || !data->exit || !data->player)
	{
		printf("Error: Failed to load textures\n");
		exit(1);
	}
}
