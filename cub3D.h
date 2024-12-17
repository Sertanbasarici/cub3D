#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <stdbool.h>
#include <fcntl.h>
#include "gnl/get_next_line.h"

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

typedef struct t_point
{
    int y;
    int x;
	int err;
}t_point;

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
	char		**_map_;
	t_point		*size_abc;
}	t_data;

typedef struct s_map_info {
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    char *floor_color;
    char *ceiling_color;
    bool no_exists;
    bool so_exists;
    bool we_exists;
    bool ea_exists;
    bool f_exists;
    bool c_exists;
    char *fclor;
    char *cclor;
	char	**maps;
} t_map_info;



typedef struct s_rgb
{
    int r;
    int g;
    int b;

} t_rgb;


char	*ft_strstr(const char *haystack, const char *needle);
bool	contains_valid_map_characters(const char *line);
void	f_fill(char **map, t_point *size, int row, int col);
void	print_map(char **map, t_point *size);
void	checkMap(int fd, char ***map_out, t_point *size_out, t_map_info *map_info); 
char	*ft_strcpy_adjusted(char *dest, const char *src);
bool	check_top_row(char **map, int col);
bool	check_bottom_row(char **map, int row, int col);
bool	check_zeros(char **map, int row, int col);
bool	is_valid_character(char c);
bool	check_map_characters(char **map, int row);
void	map_spaces(char ***map, t_point *size);
void	flood_fill(char **map, t_point *size, t_point *begin);
bool	check_map_headers(int fd, t_map_info *map_info);
void	find_starting_point(char **map, t_point *size, t_point *begin);
void	fill_flod(char **map, t_point *size, int row, int col);
bool	check_filled_map(char **map, t_point *size);
int		check_texture(char *path);
int     check_rgb_values(char *rgb);
int		check_map_textures_and_colors(t_map_info *map_info);
void	set_texture_or_color(char **tokens, t_map_info *map_info);
int		parse_and_validate_variables(char **lines, t_map_info *map_info);
void	freedouble(char **array);
int		ft_strcmp(const char *s1, const char *s2);
char	**read_lines_from_file(int fd);
bool    check_row_edges(char **map, int row);
char *ft_strreplace(char *str, char old_char, char new_char);

#endif