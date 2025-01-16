/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:37:30 by muzz              #+#    #+#             */
/*   Updated: 2025/01/16 15:39:05 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data {
    void    *mlx;            // MiniLibX instance
    void    *mlx_win;        // Window handle
    void    *img;            // Image data
    char    *addr;           // Image address
    int     bits_per_pixel;  // Image bits per pixel
    int     line_length;     // Image line length
    int     endian;          // Image endian
    int     x;               // Current x position of the circle
    int     y;               // Current y position of the circle
    int     radius;          // Circle radius
}               t_data;


#endif