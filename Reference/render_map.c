/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:07:24 by muzz              #+#    #+#             */
/*   Updated: 2025/01/17 10:07:50 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void render_map(t_data *data)
{
	for (int y = 0; y < data->map_height; y++)
	{
		for (int x = 0; x < data->map_width; x++)
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->wall, x * 50, y * 50);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->collectible, x * 50, y * 50);
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->exit, x * 50, y * 50);
			else if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				mlx_put_image_to_window(data->mlx, data->mlx_win, data->player, x * 50, y * 50);
			}
		}
	}
}
