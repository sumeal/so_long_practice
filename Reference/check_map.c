/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:33:23 by muzz              #+#    #+#             */
/*   Updated: 2025/01/17 15:14:46 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_map(char **map, int rows)
{
    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}


int is_rectangular(char **map)
{
    int i = 0;
    size_t len = ft_strlen(map[0]);

    while (map[i])
    {
		if (ft_strlen(map[i]) != len)
            return (0); // Not rectangular
        i++;
    }
    return (1);
}
int is_closed(char **map)
{
    int i = 0;
    int j;

    // Check top and bottom rows
    while (map[0][i])
        if (map[0][i++] != '1')
            return (0);
    i = 0;
    while (map[i])
        i++;
    j = 0;
    while (map[i - 1][j])
        if (map[i - 1][j++] != '1')
            return (0);
    
    // Check sides
    for (int k = 0; map[k]; k++)
        if (map[k][0] != '1' || map[k][strlen(map[k]) - 1] != '1')
            return (0);
    return (1);
}
int validate_components(char **map)
{
    int player_count = 0;
    int exit_count = 0;
    int collectible_count = 0;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            if (map[i][j] == 'P')
                player_count++;
            else if (map[i][j] == 'E')
                exit_count++;
            else if (map[i][j] == 'C')
                collectible_count++;
            else if (map[i][j] != '1' && map[i][j] != '0')
                return (0); // Invalid character
        }
    }
    return (player_count == 1 && exit_count >= 1 && collectible_count >= 1);
}
void flood_fill(char **map, int x, int y, int max_x, int max_y)
{
    if (x < 0 || y < 0 || x >= max_x || y >= max_y) // Check bounds
        return;
    if (map[x][y] == '1' || map[x][y] == 'F') // Check walls and visited cells
        return;
    
    map[x][y] = 'F';
    flood_fill(map, x + 1, y, max_x, max_y);
    flood_fill(map, x - 1, y, max_x, max_y);
    flood_fill(map, x, y + 1, max_x, max_y);
    flood_fill(map, x, y - 1, max_x, max_y);
}

char **duplicate_map(char **map, int height)
{
    char **copy = malloc(sizeof(char *) * (height + 1));
    if (!copy)
        error("Error: Memory allocation failed for map copy");

    for (int i = 0; i < height; i++)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
            error("Error: Memory allocation failed for map row copy");
    }
    copy[height] = NULL; // Null-terminate the map copy
    return copy;
}


int is_path_valid(t_data *data)
{
    printf("Checking path validity...\n");
    printf("Player position: (%d, %d)\n", data->player_x, data->player_y);

    if (data->player_x < 0 || data->player_y < 0)
    {
        printf("Error: Player position out of bounds\n");
        return (0);
    }

	char **map_copy = duplicate_map(data->map, data->map_height);
    flood_fill(map_copy, data->player_x, data->player_y, data->map_height, data->map_width);

    for (int i = 0; i < data->map_height; i++)
    {
        for (int j = 0; j < data->map_width; j++)
        {
            if ((data->map[i][j] == 'C' || data->map[i][j] == 'E') && map_copy[i][j] != 'F')
            {
                printf("Unreachable collectible or exit at: (%d, %d)\n", i, j);
                return (0);
            }
        }
    }
    return (1);
}



int check_map(t_data *data)
{
	if (!is_rectangular(data->map))
		error("Map is not rectangular");
	printf("1\n");
	if (!is_closed(data->map))
		error("Map is not closed");
	printf("2\n");
	if (!validate_components(data->map))
		error("Map components are invalid");
	printf("3\n");
	if (!is_path_valid(data))
		error("No valid path in map");
	printf("4\n");
	return (1);
}

void set_player_position(t_data *data)
{
    for (int i = 0; i < data->map_height; i++)
    {
        for (int j = 0; j < data->map_width; j++)
        {
            if (data->map[i][j] == 'P')
            {
                data->player_x = i;
                data->player_y = j;
                printf("Player position found: (%d, %d)\n", i, j); // Debug
                return;
            }
        }
    }
    error("Error: Player position not found in the map");
}
