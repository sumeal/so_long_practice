#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define ESC_KEY 65307 // Keycode for ESC key on your system
#define W_KEY 119     // W key for moving up
#define A_KEY 97      // A key for moving left
#define S_KEY 115     // S key for moving down
#define D_KEY 100     // D key for moving right
#define MOVE_SPACE 100 // Number of pixels to move the circle

typedef struct s_data {
    void    *mlx;
    void    *mlx_win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     x; // X position of the circle
    int     y; // Y position of the circle
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    draw_circle(t_data *data, int color)
{
    int     x;
    int     y;
    int     radius = 50;

    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= radius * radius)
                my_mlx_pixel_put(data, data->x + x, data->y + y, color);
            x++;
        }
        y++;
    }
}

int     key_hook(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
        exit(0);
    }
    else if (keycode == W_KEY)
	{
        printf("W key pressed\n");
		data->y -= MOVE_SPACE; // Move the circle up
	}
    else if (keycode == A_KEY)
	{
		printf("A key pressed\n");
        data->x -= MOVE_SPACE; // Move the circle left
	}
    else if (keycode == S_KEY)
	{
		printf("S key pressed\n");
        data->y += MOVE_SPACE; // Move the circle down
	}
    else if (keycode == D_KEY)
	{
		printf("D key pressed\n");
        data->x += MOVE_SPACE; // Move the circle right
	}

    mlx_clear_window(data->mlx, data->mlx_win);
    draw_circle(data, 0x00FF00); // Draw a green circle
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);

    return (0);
}

int     main(void)
{
    t_data  data;

    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 1280, 720, "Move the Circle");
    data.img = mlx_new_image(data.mlx, 1280, 720);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    data.x = 640; // Initial position of the circle (center of the window)
    data.y = 360;

    mlx_key_hook(data.mlx_win, key_hook, &data);
    mlx_loop(data.mlx);

    return (0);
}
