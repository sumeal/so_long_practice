/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:20:15 by muzz              #+#    #+#             */
/*   Updated: 2025/01/21 10:34:06 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	char	**map;
	char	**visited;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*wall;
	void	*grass;
	void	*cross;
	int		qty_collectible;
	int		qty_player;
	int		qty_exit;
	int		player_x;
	int		player_y;
	int		move;
	
}			t_data;

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

char *ft_strdup_sl(char *str)
{
	char *new_str;
	int i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str)));
	if (!new_str)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	get_resolution(t_data *data)
{
	int fd;
	char *line;

	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		print_error("Error opening the map\n");
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		data->width = (int)ft_strlen(line);
		free(line);
		data->height++;
	}
	free(line);
	close(fd);
	data->map = malloc(sizeof(char *) * (data->height) + 1);
	if (!data->map)
		print_error("Malloc failed\n");
}
void get_data(t_data *data)
{
	int fd;
	char *line;
	int	i;
	
	i = 0;
	data->height = 0;
	data->width = 0;
	data->move = -1;
	get_resolution(data);
	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
		print_error("Error opening the map\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		data->map[i++] = ft_strdup_sl(line);
		free(line);
	}
	data->map[i] = NULL;
	free(line);
	close(fd);
}

int is_rectangular(t_data *data)
{
    int i;
    size_t len;

    i = 0;
    len = ft_strlen(data->map[0]);
    while (data->map[i])
    {
        if (ft_strlen(data->map[i]) != len)
            return (0);
        i++;
    }
    return (1);
}

int is_closed(t_data *data)
{
    int i;
    int j;
    char **map;

    map = data->map;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (i == 0 || i == data->height - 1 
				|| j == 0 || j == data->width - 1) 
            {
                if (map[i][j] != '1')
                    return (0);
			}
            j++;
        }
        i++;
    }
    return (1);
}
int	check_valid(t_data *data)
{
	int i;
	int j;
	char **map;

	map = data->map;
	i = -1;
	data->qty_player = 0;
	data->qty_collectible = 0;
	data->qty_exit = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
			{
				(data->qty_player)++;
				data->player_x = j;
				data->player_y = i;
			}
			if (map[i][j] == 'C')
				(data->qty_collectible)++;
			if (map[i][j] == 'E')
				(data->qty_exit)++;
		}
	}
	if (data->qty_player != 1 || data->qty_collectible < 1 || data->qty_exit != 1)
		return(0);
	return (1);
}

int	is_valid(t_data *data)
{
	int i;
	int j;
	char **map;

	map = data->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'P' && map[i][j] != 'C' && map[i][j] != 'E')
				return (0);
			j++;
		}
		i++;
	}
	if (!check_valid(data))
		return (0);
	return (1);
}

void init_visited(t_data *data)
{
    int i;
    int j;

    data->visited = malloc(sizeof(char *) * data->height);
    if (!data->visited)
        print_error("Malloc failed\n");

    i = 0;
    while (i < data->height)
    {
        data->visited[i] = malloc(sizeof(char) * data->width);
        if (!data->visited[i])
            print_error("Malloc failed\n");
        
        j = 0;
        while (j < data->width)
        {
            data->visited[i][j] = 0;
            j++;
        }
        i++;
    }
}

int is_valid_move(int x, int y, t_data *data)
{
    if (x < 0 || y < 0 || x >= data->width || y >= data->height)
        return 0;
    if (data->map[y][x] == '1' || data->visited[y][x] == 1)
        return 0;
    return 1;
}

void flood_fill(int x, int y, t_data *data)
{
    if (!is_valid_move(x, y, data))
        return;
    data->visited[y][x] = 1;
    flood_fill(x + 1, y, data);
    flood_fill(x - 1, y, data);
    flood_fill(x, y + 1, data);
    flood_fill(x, y - 1, data);
}

void free_visited(t_data *data)
{
    int i;

    i = 0;
    while (i < data->height)
    {
        free(data->visited[i]);
        i++;
    }
    free(data->visited);
}

int is_path_valid(t_data *data)
{
    int i;
    int j;

    init_visited(data);
    flood_fill(data->player_x, data->player_y, data);
    i = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == 'C' && !data->visited[i][j])
            {
                free_visited(data);
                return (0);
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == 'E' && !data->visited[i][j])
            {
                free_visited(data);
                return (0);
            }
            j++;
        }
        i++;
    }
    free_visited(data);
    return (1);
}

void check_map(t_data *data)
{
    if (data->height < 3 || data->width < 3)
        print_error("Map too small\n");
    if (!is_valid(data))
        print_error("Map not valid\n");
    if (!is_rectangular(data))
        print_error("Map not rectangular\n");
    if (!is_closed(data))
        print_error("Map not closed\n");
    if (!is_path_valid(data))
        print_error("Path not valid\n");
}


void	load_texture(t_data *data)
{
	int width;
	int height;
	
	width = 50;
	height = 50;
	data->wall = mlx_xpm_file_to_image(data->mlx, "graphic/wall.xpm", &width, &height);
	data->player = mlx_xpm_file_to_image(data->mlx, "graphic/player.xpm", &width, &height);
	data->collectible = mlx_xpm_file_to_image(data->mlx, "graphic/collectible.xpm", &width, &height);
	data->exit = mlx_xpm_file_to_image(data->mlx, "graphic/exit.xpm", &width, &height);
	data->grass = mlx_xpm_file_to_image(data->mlx, "graphic/grass.xpm", &width, &height);
	data->cross = mlx_xpm_file_to_image(data->mlx, "graphic/cross.xpm", &width, &height);
	if (!data->wall || !data->player || !data->collectible || !data->exit || !data->grass || !data->cross)
	{
		printf("Error loading texture\n");
		exit(1);
	}
}

void	render_map(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall, x * 50, y * 50);
			else if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->player, x * 50, y * 50);
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collectible, x * 50, y * 50);
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exit, x * 50, y * 50);
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->grass, x * 50, y * 50);
			x++;
		}
		y++;
	}
}

void update_map(t_data *data, int old_x, int old_y, int new_x, int new_y)
{

    if (data->map[new_y][new_x] == 'E')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->cross, new_x * 50, new_y * 50);
		mlx_put_image_to_window(data->mlx, data->win, data->grass, old_x * 50, old_y * 50);
	}
	else if (data->map[old_y][old_x] == 'E')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->exit, old_x * 50, old_y * 50);
		mlx_put_image_to_window(data->mlx, data->win, data->player, new_x * 50, new_y * 50);	
	}
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, data->grass, old_x * 50, old_y * 50);
    	mlx_put_image_to_window(data->mlx, data->win, data->player, new_x * 50, new_y * 50);
	}
}

int handle_key(int keycode, t_data *data)
{
    int new_x = data->player_x;
    int new_y = data->player_y;

    if (keycode == 65361) // Left arrow
        new_x--;
    else if (keycode == 65362) // Up arrow
        new_y--;
    else if (keycode == 65363) // Right arrow
        new_x++;
    else if (keycode == 65364) // Down arrow
        new_y++;
    else if (keycode == 65307) // Escape key
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    // Check for valid move
    if (data->map[new_y][new_x] != '1') // Avoid walls
    {
        if (data->map[new_y][new_x] == 'E' && data->qty_collectible == 0)
		{
			printf("  __     ______  _    _  __          _______ _   _ _\n");
			printf("  \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | | |\n");
			printf("   \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| | |\n");
			printf("    \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` | |\n");
			printf("     | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  |_|\n");
			printf("     |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_(_)\n");
        	mlx_destroy_window(data->mlx, data->win);
           	exit(0);
		}
		if (data->map[new_y][new_x] == 'C')
        	data->qty_collectible--;
		if (data->map[new_y][new_x] == 'E')
		{
			update_map(data, data->player_x, data->player_y, new_x, new_y);
			data->map[data->player_y][data->player_x] = '0'; // Clear old position			
			data->player_x = new_x;
       		data->player_y = new_y;
		}
		else if (data->map[data->player_y][data->player_x] == 'E')
		{
			data->map[data->player_y][data->player_x] = 'E'; // Clear old position
			data->map[new_y][new_x] = 'P';                  // Set new position
			update_map(data, data->player_x, data->player_y, new_x, new_y);
			data->player_x = new_x;
	   		data->player_y = new_y;
		}
		else
		{
		data->map[data->player_y][data->player_x] = '0'; // Clear old position
       	data->map[new_y][new_x] = 'P';                  // Set new position
       	update_map(data, data->player_x, data->player_y, new_x, new_y);
		data->player_x = new_x;
       	data->player_y = new_y;
		}
	}
	(data->move)++;
	if (data->move > 0)
		printf("Current Move: %d\n", data->move);
	printf("%d", keycode);
    return (0);
}
int close_window(int button, void *param)
{
    // Window close event
    if (button == 0)
    {
        mlx_destroy_window(param, param);  // Destroy the window
        exit(0);  // Exit the program
    }
    return 0;
}
int main(void)
{
	t_data data;

	get_data(&data);
	check_map(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, (data.width * 50), (data.height *50), "So Long");
	load_texture(&data);
	render_map(&data);
    mlx_hook(data.win, 17, 0, close_window, data.mlx);		
	printf("Player position is %d, %d\n", data.player_x, data.player_y);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
}