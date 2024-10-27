/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasari <sebasari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:35:43 by sebasari          #+#    #+#             */
/*   Updated: 2024/10/27 15:46:33 by sebasari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define mapWidth 10
#define mapHeight 10
#define screenWidth 800
#define screenHeight 800
#define tileSize 80
#define PI 3.14159

typedef struct p_data
{
	int			px;
	int			py;
	double		angle;
	double		vector_x;
	double		vector_y;
	double		vector;
}	player_data;

typedef struct s_data
{
	player_data	player;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_data;

int map[mapHeight][mapWidth] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

double degree_to_radyan(double degree)
{
	double radyan;
	radyan = degree * (PI / 180);
	return (radyan);
}

void rotate(player_data *player, double angle_offset)
{
    player->angle += angle_offset;

    if (player->angle >= 360)
        player->angle -= 360;
    else if (player->angle < 0)
        player->angle += 360;

    double rad = degree_to_radyan(player->angle);

    // Update the vector_x and vector_y based on the new angle
    player->vector_x = cos(rad) * player->vector;
    player->vector_y = sin(rad) * player->vector;
}



t_data	*player_init(t_data *data)
{
	data->player.vector_y = 70;
	data->player.vector_x = 0;
	data->player.angle = 0;
	data->player.vector = 70;
	data->player.px = 300;
	data->player.py = 300;
	return (data);
}

void	clear_player(t_data *data, double degree)
{
	int char_width = 20;
    int char_height = 70;

    double center_x = data->player.px + char_width / 2;
    double center_y = data->player.py + char_height / 2;

    double cos_rad = cos(degree_to_radyan(degree));
    double sin_rad = sin(degree_to_radyan(degree));

    for (int y = 0; y < char_height; y++) {
        for (int x = 0; x < char_width; x++) {
            double orig_x = data->player.px + x;
            double orig_y = data->player.py + y;
            int rotated_x = (int)(center_x + (orig_x - center_x) * cos_rad - (orig_y - center_y) * sin_rad);
            int rotated_y = (int)(center_y + (orig_x - center_x) * sin_rad + (orig_y - center_y) * cos_rad);

            int color = 0x000000;
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, rotated_x, rotated_y, color);
        }
    }
}

int	close_window(void *param)
{
	(void)param;
	system("leaks cub3D");
	exit(0);
}

void draw_player(t_data *data, double degree)
{
    int char_width = 20;
    int char_height = 70;

    double center_x = data->player.px + char_width / 2;
    double center_y = data->player.py + char_height / 2;

    double cos_rad = cos(degree_to_radyan(degree));
    double sin_rad = sin(degree_to_radyan(degree));

    for (int y = 0; y < char_height; y++)
	{
        for (int x = 0; x < char_width; x++)
		{
            double orig_x = data->player.px + x;
            double orig_y = data->player.py + y;
            int rotated_x = (int)(center_x + (orig_x - center_x) * cos_rad - (orig_y - center_y) * sin_rad);
            int rotated_y = (int)(center_y + (orig_x - center_x) * sin_rad + (orig_y - center_y) * cos_rad);

            int color = 0x0000FF;
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, rotated_x, rotated_y, color);
        }
    }
}


void draw(t_data *data, int x_nd, int y_nd, int color)
{
	for (int y = y_nd * tileSize; y < (y_nd + 1) * tileSize; y++)
	{
		for (int x = x_nd * tileSize; x < (x_nd + 1) * tileSize; x++)
		{
				mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		}
	}
}


void draw_map(t_data *data)
{
	int x, y;

	for (y = 0; y < mapHeight; y++)
	{
		for (x = 0; x < mapWidth; x++)
		{
			if (map[y][x] == 1)
				draw(data, x, y, 0xFFFFFF);
			else if (map[y][x] == 0)
				draw(data, x, y, 0x000000);
		}
	}
}

int key_hook(int keycode, void *param)
{
    t_data *data = (t_data *)param;
	double	angle = 0;
	double	pixel_x = 0;
	double	pixel_y = 0;
    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)  // ESC to exit
    {
        printf("ESC pressed, closing the window.\n");
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data->mlx_ptr);
        return 0;
    }

    if (keycode == 124)  // Right arrow key (rotate clockwise)
    {
		angle = data->player.angle;
		rotate(&data->player, 10);  // Rotate by +10 degrees
	}
	else if (keycode == 123)
	{
		angle = data->player.angle;
		rotate(&data->player, -10);
	}

	if (keycode == 2 && data->player.px > 0 && data->player.py > 0)
	{
		pixel_x = data->player.px;
		data->player.px++;
	}
	if (keycode == 0 && data->player.px > 0 && data->player.py > 0)
	{
		pixel_x = data->player.px;
		data->player.px--;
	}
	if (keycode == 13 && data->player.px > 0 && data->player.py > 0)
	{
		pixel_y = data->player.py;
		data->player.py--;
	}
	if (keycode == 1 && data->player.px > 0 && data->player.py > 0)
	{
		pixel_y = data->player.py;
		data->player.py++;
	}
	clear_player(data, angle);
	draw_player(data, data->player.angle);  // Use updated angle for rotation
	return 0;
}


int main()
{

	t_data *data;

	data = malloc(sizeof(t_data));
	data = player_init(data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, screenWidth, screenHeight, "Minilibx Penceresi");
	draw_map(data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, NULL);
	mlx_loop(data->mlx_ptr);
	return (0);
}
