/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:20:15 by muzz              #+#    #+#             */
/*   Updated: 2025/01/22 09:10:29 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
void free_all(t_data *data)
{
    int i;

    // Free map data
    i = 0;
    while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
	free_visited(data);
    mlx_destroy_image(data->mlx, data->wall);
    mlx_destroy_image(data->mlx, data->player);
    mlx_destroy_image(data->mlx, data->collectible);
    mlx_destroy_image(data->mlx, data->exit);
    mlx_destroy_image(data->mlx, data->grass);
    mlx_destroy_image(data->mlx, data->cross);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
	free(data->mlx);
}


void	print_error(char *str, t_data *data)
{
	printf("%s\n", str);
	free_all(data);
	exit(1);
}

int	ft_strnstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;

	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j] == '\0')
				return (1);
			j++;
		}
		if (needle[j] == '\0')
			return (0);
		i++;
	}
	return (0);
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

	fd = open(data->map_file, O_RDONLY);
	if (fd == -1)
		print_error("Error opening the map\n", data);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		data->width = (int)ft_strlen(line);
		free(line);
		data->height++;
	}
	close(fd);
	data->map = malloc(sizeof(char *) * ((data->height) + 1));
	if (!data->map)
		print_error("Malloc failed\n", data);
}
void get_data(t_data *data)
{
	int fd;
	char *line;
	int	i;
	
	i = 0;
	data->pixel_scale = 50; // 50 pixels per square
	data->height = 0;
	data->width = 0;
	data->move = -1; // Start at -1 to avoid counting the first move
	get_resolution(data);
	fd = open(data->map_file, O_RDONLY);
	if (fd == -1)
		print_error("Error: Opening the map.\n", data);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		data->map[i++] = ft_strdup_sl(line);
		if (!data->map[i - 1])
			print_error("Malloc failed\n", data);
		free(line);
	}
	data->map[i] = NULL;
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
        print_error("Malloc failed\n", data);

    i = 0;
    while (i < data->height)
    {
        data->visited[i] = malloc(sizeof(char) * data->width);
        if (!data->visited[i])
            print_error("Malloc failed\n", data);
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
        return (0);
    if (data->map[y][x] == '1' || data->visited[y][x] == 1)
        return (0);
    return (1);
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
				return (0);
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
				return (0);
            j++;
        }
        i++;
    }
    return (1);
}

void check_map(t_data *data)
{
    if (data->height < 3 || data->width < 3)
        print_error("Error: Map too small\n", data);
    if (!is_valid(data))
        print_error("Error: Map not valid\n", data);
    if (!is_rectangular(data))
        print_error("Error: Map not rectangular\n", data);
    if (!is_closed(data))
        print_error("Error: Map not closed\n", data);
    if (!is_path_valid(data))
        print_error("Error: Path not valid\n", data);
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
		print_error("Error: Loading textures\n", data);
}

void	check_pixel_scale(t_data *data)
{
	if ((data->pixel_scale) * (data->width) > 1920 || (data->pixel_scale) * (data->height) > 1080)
		print_error("Error: Map too big\n", data);
}

void	render_map(t_data *data)
{
	int x;
	int y;
	
	check_pixel_scale(data);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall, x * (data->pixel_scale), y * (data->pixel_scale));
			else if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx, data->win, data->player, x * (data->pixel_scale), y * (data->pixel_scale));
			else if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collectible, x * (data->pixel_scale), y * (data->pixel_scale));
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->exit, x * (data->pixel_scale), y * (data->pixel_scale));
			else if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->grass, x * (data->pixel_scale), y * (data->pixel_scale));
			x++;
		}
		y++;
	}
}

void update_map(t_data *data, int old_x, int old_y, int new_x, int new_y)
{

	if (data->map[new_y][new_x] == 'E')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->cross, new_x * (data->pixel_scale), new_y * (data->pixel_scale));
		mlx_put_image_to_window(data->mlx, data->win, data->grass, old_x * (data->pixel_scale), old_y * (data->pixel_scale));
	}
	else if (data->map[old_y][old_x] == 'E')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->exit, old_x * (data->pixel_scale), old_y * (data->pixel_scale));
		mlx_put_image_to_window(data->mlx, data->win, data->player, new_x * 50, new_y * 50);	
	}
	else
	{
		mlx_put_image_to_window(data->mlx, data->win, data->grass, old_x * (data->pixel_scale), old_y * (data->pixel_scale));
    	mlx_put_image_to_window(data->mlx, data->win, data->player, new_x * (data->pixel_scale), new_y * (data->pixel_scale));
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
        printf("Exiting...\n");
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
    	free_all(data);
		exit(0);
    }
    // Check for valid move
    if (data->map[new_y][new_x] != '1') // Avoid walls
    {
		(data->move)++;
		if (data->move > 0)
			printf("Current Move: %d\n", data->move);        
		if (data->map[new_y][new_x] == 'E' && data->qty_collectible == 0)
		{
			printf("  __     ______  _    _  __          _______ _   _ _\n");
			printf("  \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | | |\n");
			printf("   \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| | |\n");
			printf("    \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` | |\n");
			printf("     | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  |_|\n");
			printf("     |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_(_)\n\n");
           	free_all(data);
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
			printf("You need to k!ll all the rats first\n");
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
	return (0);
}
int close_window(int keycode, t_data *data)
{
    (void)keycode;
    (void)data;
    printf("Exiting...\n");
	free_all(data);
    exit(0);  // Exit the program
    return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	data = (t_data){0};
	if (argc != 2)
    {
        printf("Usage: %s <map_file.ber>\n", argv[0]);
        return (1);
    }
    data.map_file = argv[1];
    if (!ft_strnstr(data.map_file, ".ber"))
    {
        printf("Error: File must have a .ber extension.\n");
        return (1);
    }
	get_data(&data);
	check_map(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, (data.width * 50), (data.height *50), "So Long");
	load_texture(&data);
	render_map(&data);
	mlx_hook(data.win, 17, 0, close_window, data.mlx);		
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
}

