/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:20:31 by muzz              #+#    #+#             */
/*   Updated: 2025/01/22 09:10:46 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	*map_file;
	int		pixel_scale;
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



#endif