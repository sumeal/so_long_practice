#include "minilibx-linux/mlx.h"
#include <stdio.h>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 400
#define TILE_SIZE 50  // Size of each texture tile

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	void	*texture;
	int		texture_width;
	int		texture_height;
}				t_data;

int	main(void)
{
	t_data	data;
	int		x;
	int		y;

	// Initialize mlx
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Texture Replication");

	// Load the texture image (ensure the texture is 50x50)
	data.texture = mlx_xpm_file_to_image(data.mlx, "graphic/grass1.xpm", &data.texture_width, &data.texture_height);
	if (!data.texture)
	{
		printf("Error loading texture image!\n");
		return (1);
	}

	// Ensure the texture is 50x50 (if it's not, you may need to resize it)
	if (data.texture_width != TILE_SIZE || data.texture_height != TILE_SIZE)
	{
		printf("Error: The texture must be 50x50 pixels.\n");
		return (1);
	}

	// Loop through the window and draw the texture tile at intervals
	for (y = 0; y < WIN_HEIGHT; y += TILE_SIZE)  // Loop vertically with a step of 50
	{
		for (x = 0; x < WIN_WIDTH; x += TILE_SIZE)  // Loop horizontally with a step of 50
		{
			mlx_put_image_to_window(data.mlx, data.mlx_win, data.texture, x, y);
		}
	}

	// Keep the window open
	mlx_loop(data.mlx);
	return (0);
}
