/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:48:28 by muzz              #+#    #+#             */
/*   Updated: 2025/01/17 15:13:34 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


#include <stdio.h>
#include <stdlib.h>

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
void initialize_data(t_data *data)
{
    data->player_x = -1; // Default invalid values
    data->player_y = -1;
    data->map = NULL;
    data->map_height = 0;
    data->map_width = 0;
}

void get_data(t_data *data)
{
    int fd = open("map1.ber", O_RDONLY);
    if (fd < 0)
        error("Error: Unable to open map file");

    int i = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        data->map[i] = ft_strdup(line);
        free(line);
        i++;
    }
    data->map[i] = NULL; // Null-terminate the map
    data->map_height = i;
    data->map_width = ft_strlen(data->map[0]); // Assume all rows have the same width
    close(fd);

    set_player_position(data); // Set player's position
}


int main(void)
{
	t_data data;
	
	initialize_data(&data);
	get_data(&data);
	printf("1\n");
	if (!check_map(&data))
	{
		printf("Map is invalid\n");
		exit(1);
	}
	printf("2\n");
	data.mlx = mlx_init();
	printf("3\n");
	data.mlx_win = mlx_new_window(data.mlx, 1000, 400, "So Long");
	printf("4\n");
	load_textures(&data);
	render_map(&data);	
	mlx_key_hook(data.mlx_win, handle_keypress, &data);
	mlx_loop(data.mlx);
	return (0);
}