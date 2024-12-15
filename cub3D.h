#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

#define Width 25
#define Height 25
#define texWidth 64
#define texHeight 64
#define screenWidth 800
#define screenHeight 600
#define PI 3.14159
#define ESC 65307
#define key_D 100
#define key_A 97
#define key_W 119
#define key_S 115
#define ROTATE_R 65363
#define ROTATE_L 65361

typedef struct s_img
{
	void	*img;
	char	*data;
	int		endian;
	int		bits_per_pixel;
	int		sizeline;
}   t_img;

typedef struct p_data
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	sideDistX;
	double	sideDistY;
}	player_data;

typedef struct s_data
{
	player_data	player;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		big_img;
	t_img		east;
	t_img		north;
	t_img		south;
	t_img		west;
	int			width;
	int			height;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			y;
	int			x;
	double		deltaDistX;
	double		deltaDistY;
	int			hit;
	int			stepX;
	int			stepY;
	int			color;
	int			drawStart;
	int			drawEnd;
	double		perpWallDist;
	int			ceil_color;
	int			floor_color;
	int			lineHeight;
	int			side;
	double		movespeed;
}	t_data;




#endif