#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define ESC_KEY 65307 // Keycode for ESC key on your system

typedef struct s_data {
    void    *mlx;
    void    *mlx_win;
    void    *cursor_img; // Custom cursor image
    int     cursor_x;    // X position of the cursor
    int     cursor_y;    // Y position of the cursor
}               t_data;

int     key_hook(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(data->mlx, data->mlx_win);
        exit(0);
    }
    return (0);
}

// Move cursor event handler
int     motion_notify(int x, int y, t_data *data)
{
    data->cursor_x = x;
    data->cursor_y = y;

    mlx_clear_window(data->mlx, data->mlx_win); // Clear the window
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->cursor_img, x - 16, y - 16); // Draw the cursor

    return (0);
}

int     main(void)
{
    t_data  data;

    // Initialize mlx and window
    data.mlx = mlx_init();
    data.mlx_win = mlx_new_window(data.mlx, 1280, 720, "Custom Cursor");

    // Load cursor image (replace "cursor.xpm" with the path to your image)
    data.cursor_img = mlx_xpm_file_to_image(data.mlx, "graphic/cursor.xpm", &data.cursor_x, &data.cursor_y);

    if (!data.cursor_img)
    {
        printf("Error loading cursor image!\n");
        return (1);
    }

    // Set the mouse motion event to track mouse movement
    mlx_hook(data.mlx_win, 6, 1L << 6, motion_notify, &data);

    // Set the key press event to close the window when ESC is pressed
    mlx_key_hook(data.mlx_win, key_hook, &data);

    // Enter the event loop
    mlx_loop(data.mlx);

    return (0);
}
