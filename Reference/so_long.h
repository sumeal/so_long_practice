/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:37:30 by muzz              #+#    #+#             */
/*   Updated: 2025/01/17 15:12:57 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_data {
    void	*mlx;            // MiniLibX instance
    void	*mlx_win;        // Window handle
	char	**map;            // Map data
	int		map_width;       // Map width
	int		map_height;      // Map height
	void	*player;          // Player texture
	void	*wall;            // Wall texture
	void	*exit;            // Exit texture
	void	*collectible;     // Collectible texture
	int		collectibles;    // Number of collectibles
	int		player_x;        // Player x position
	int		player_y;        // Player y position
	int		player_moves;    // Player moves
}               t_data;

void load_textures(t_data *data);
int check_map(t_data *data);
void load_textures(t_data *data);
void render_map(t_data *data);
char	*ft_strdup(const char *s);
int handle_keypress(int keycode, t_data *data);
void error(const char *message);
void set_player_position(t_data *data);

#endif