/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mechanism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:47:23 by muzz              #+#    #+#             */
/*   Updated: 2025/01/22 10:48:01 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_key(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == 65361)
		new_x--;
	else if (keycode == 65362)
		new_y--;
	else if (keycode == 65363)
		new_x++;
	else if (keycode == 65364)
		new_y++;
	else if (keycode == 65307)
	{
		printf("Exiting...\n");
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free_all(data);
		exit(0);
	}
	if (data->map[new_y][new_x] != '1')
		handle_key2(new_x, new_y, data);
	return (0);
}

void	handle_key2(int new_x, int new_y, t_data *data)
{
	(data->move)++;
	if (data->move > 0)
		printf("Current Move: %d\n", data->move);
	if (data->map[new_y][new_x] == 'E' && data->qty_collect == 0)
	{
		printf("  __     ______  _    _  __          _______ _   _ _\n");
		printf("  \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | | |\n");
		printf("   \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| | |\n");
		printf("    \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` | |\n");
		printf("     | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  |_|\n");
		printf("     |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_(_)\n");
		printf("\n");
		free_all(data);
		exit(0);
	}
	if (data->map[new_y][new_x] == 'C')
		data->qty_collect--;
	handle_key3(new_x, new_y, data);
}

void	handle_key3(int new_x, int new_y, t_data *data)
{
	if (data->map[new_y][new_x] == 'E')
	{
		update_map(data, new_x, new_y);
		data->map[data->player_y][data->player_x] = '0';
		data->player_x = new_x;
		data->player_y = new_y;
		printf("You need to k!ll all the rats first\n");
	}
	else if (data->map[data->player_y][data->player_x] == 'E')
	{
		data->map[data->player_y][data->player_x] = 'E';
		data->map[new_y][new_x] = 'P';
		update_map(data, new_x, new_y);
		data->player_x = new_x;
		data->player_y = new_y;
	}
	else
	{
		data->map[data->player_y][data->player_x] = '0';
		data->map[new_y][new_x] = 'P';
		update_map(data, new_x, new_y);
		data->player_x = new_x;
		data->player_y = new_y;
	}
}
