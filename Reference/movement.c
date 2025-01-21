/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:08:45 by muzz              #+#    #+#             */
/*   Updated: 2025/01/17 10:09:34 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_player(t_data *data, int dx, int dy)
{
	int new_x = data->player_x + dx;
	int new_y = data->player_y + dy;

	if (data->map[new_y][new_x] == '1') // Can't move into a wall
		return;
	if (data->map[new_y][new_x] == 'C') // Collect item
		data->collectibles--;
	if (data->map[new_y][new_x] == 'E' && data->collectibles == 0) // Exit when all collected
		exit(0);

	data->map[data->player_y][data->player_x] = '0'; // Clear old position
	data->player_x = new_x;
	data->player_y = new_y;
	data->map[new_y][new_x] = 'P'; // Update new position

	render_map(data); // Re-render the map
}

int handle_keypress(int keycode, t_data *data)
{
	if (keycode == 53) // ESC key to exit
		exit(0);
	else if (keycode == 13) // W key
		move_player(data, 0, -1);
	else if (keycode == 0) // A key
		move_player(data, -1, 0);
	else if (keycode == 1) // S key
		move_player(data, 0, 1);
	else if (keycode == 2) // D key
		move_player(data, 1, 0);
	return (0);
}

