/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:11:59 by muzz              #+#    #+#             */
/*   Updated: 2025/01/23 08:33:49 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_visited(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->visited[i]);
		i++;
	}
	free(data->visited);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (data->map[++i])
		free(data->map[i]);
	free(data->map);
	if (data->visited)
		free_visited(data);
	if (data->wall)
		mlx_destroy_image(data->mlx, data->wall);
	if (data->player)
		mlx_destroy_image(data->mlx, data->player);
	if (data->collect)
		mlx_destroy_image(data->mlx, data->collect);
	if (data->exit)
		mlx_destroy_image(data->mlx, data->exit);
	if (data->grass)
		mlx_destroy_image(data->mlx, data->grass);
	if (data->cross)
		mlx_destroy_image(data->mlx, data->cross);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)	
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	print_error(char *str, t_data *data)
{
	printf("%s", str);
	free_all(data);
	exit(1);
}

int	close_window(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	printf("Exiting...\n");
	free_all(data);
	exit(0);
	return (0);
}

void	check_pixel_scale(t_data *data)
{
	if ((data->pixel_scale) * (data->width) > 1920 || (data->pixel_scale) * (data->height) > 1080)
		print_error("Error\nMap Too Big\n", data);
}



