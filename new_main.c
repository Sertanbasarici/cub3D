#include "cub3D.h"

int	close_window(void *param)
{
	(void)param;
	system("leaks cub3D");
	exit(0);
}

int ft_error(int num, char *str)
{
    if (num == 1)
        ft_putstr_fd(str, 2);
    return (0);
}

int worldMap[Width][Height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->data + (y * img->sizeline + x * (img->bits_per_pixel / 8));
	*(int *)pixel = color;
}

unsigned int	get_pixel_in_tex(t_img tex, int x, int y)
{
	char	*dst;

	dst = tex.data + (y * tex.sizeline + x * (tex.bits_per_pixel / 8));
	return (*((unsigned int *)dst));
}

void	calc_texture_pixel_color(t_data *data, int x)
{
	if (data->y < data->drawStart)
		img_pix_put(&data->big_img, x, data->y, data->ceil_color);
    else if (data->y >= data->drawStart && data->y <= data->drawEnd)
	{
		data->tex_y = (int)data->tex_pos & (64 - 1);
		data->tex_pos += data->step;
		if (data->side == 0 && data->player.rayDirX > 0)
			data->color = get_pixel_in_tex(data->east, data->tex_x, data->tex_y);
        else if (data->side == 0 && data->player.rayDirX < 0)
        	data->color = get_pixel_in_tex(data->west, data->tex_x, data->tex_y);
        else if (data->side == 1 && data->player.rayDirY > 0)
        	data->color = get_pixel_in_tex(data->north, data->tex_x, data->tex_y);
        else if (data->side == 1 && data->player.rayDirY < 0)
        	data->color = get_pixel_in_tex(data->south, data->tex_x, data->tex_y);
        img_pix_put(&data->big_img, x, data->y, data->color);
	}
	else
		img_pix_put(&data->big_img, x, data->y, data->floor_color);
}

void    raycasting_DDA(t_data *data)
{
    while (data->hit == 0)
    {
        if (data->player.sideDistX < data->player.sideDistY)
        {
            data->player.sideDistX += data->deltaDistX;
            data->player.mapX += data->stepX;
            data->side = 0;
        }
        else
        {
            data->player.sideDistY += data->deltaDistY;
            data->player.mapY += data->stepY;
            data->side = 1;
        }
        if (worldMap[data->player.mapX][data->player.mapY] > 0)
            data->hit = 1;
    }
}


void    raycasting_continue(t_data *data)
{
    data->hit = 0;
    data->side = 0;
    if (data->player.rayDirX < 0)
    {
        data->stepX = -1;
        data->player.sideDistX = (data->player.posX - data->player.mapX) * data->deltaDistX;
    }
    else
    {
        data->stepX = 1;
        data->player.sideDistX = (data->player.mapX + 1.0 - data->player.posX) * data->deltaDistX;
    }
    if (data->player.rayDirY < 0)
    {
        data->stepY = -1;
        data->player.sideDistY = (data->player.posY - data->player.mapY) * data->deltaDistY;
    }
    else
    {
        data->stepY = 1;
        data->player.sideDistY = (data->player.mapY + 1.0 - data->player.posY) * data->deltaDistY;
    }
}
void    avoid_fisheye(t_data *data)
{
    if (data->side == 0)
        data->perpWallDist = (data->player.sideDistX - data->deltaDistX);
    else
        data->perpWallDist = (data->player.sideDistY - data->deltaDistY);
    data->lineHeight = (int)(screenHeight/ data->perpWallDist);
    data->drawStart = -data->lineHeight / 2 + screenHeight / 2;
    data->drawEnd = data->lineHeight / 2 + screenHeight / 2;
    if (data->drawStart < 0)
        data->drawStart = 0;
    data->drawEnd = data->lineHeight / 2 + screenHeight / 2;
    if (data->drawEnd >= screenHeight)
        data->drawEnd = screenHeight - 1;
}

void    handle_textures(t_data *data)
{
    if (data->side == 0)
    	data->wall_x = data->player.posY + (data->perpWallDist * data->player.rayDirY);
    else
        data->wall_x = data->player.posX + (data->perpWallDist * data->player.rayDirX);
    data->wall_x -= floor(data->wall_x);
    data->tex_x = (int)(data->wall_x * (double)64);
    if(data->side == 0 && data->player.rayDirX > 0)
        data->tex_x = texWidth - data->tex_x - 1;
    if(data->side == 1 && data->player.rayDirY < 0)
        data->tex_x = texWidth - data->tex_x - 1;
    data->step = (1.0 * 64) / data->lineHeight;
    data->tex_pos = (data->drawStart - screenHeight / 2 + data->lineHeight / 2) * data->step;
    while (data->y < screenHeight)
    {
    	calc_texture_pixel_color(data, data->x);
    	data->y++;
    }
    data->y = 0;
}
void    raycasting_starts(t_data *data)
{
    data->x = 0;
    while (data->x < screenWidth)
    {
        data->player.cameraX = (2 * data->x / (double)screenWidth) - 1;
        data->player.rayDirX = data->player.dirX + (data->player.planeX * data->player.cameraX);
        data->player.rayDirY = data->player.dirY + (data->player.planeY * data->player.cameraX);
        data->player.mapX = (int)data->player.posX;
        data->player.mapY = (int)data->player.posY;
        if (data->player.rayDirX == 0)
            data->deltaDistX = 1e30;
        else
            data->deltaDistX = fabs(1 / data->player.rayDirX);
        if (data->player.rayDirY == 0)
             data->deltaDistY = 1e30;
        else
            data->deltaDistY = fabs(1 / data->player.rayDirY);
        raycasting_continue(data);
        raycasting_DDA(data);
        avoid_fisheye(data);
        handle_textures(data);
        data->x++;
    }
}

int draw_scene(t_data *data)
{
    raycasting_starts(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->big_img.img, 0, 0);
    return 0;
}

int key_press()
{
    return (0);
}


void    close_screen(int keycode, t_data *data)
{
    if (keycode == ESC)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        exit(0);
    }
}

void    move_r_and_l(int keycode, t_data *data)
{
    if (keycode == key_D)
    {
        if (worldMap[(int)(data->player.posX + data->player.planeX)][(int)(data->player.posY + data->player.planeY)] == 0)
        {
            data->player.posX += data->player.planeX * data->movespeed;
            data->player.posY += data->player.planeY * data->movespeed;
        }
    }
    if (keycode == key_A)
    {
        if (worldMap[(int)(data->player.posX - data->player.planeX)][(int)(data->player.posY - data->player.planeY)] == 0)
        {
            data->player.posX -= data->player.planeX * data->movespeed;
            data->player.posY -= data->player.planeY * data->movespeed;
        }
    }    
}
void    move_f_and_b(int keycode, t_data *data)
{
    if (keycode == key_W)
    {
        if (worldMap[(int)(data->player.posX + data->player.dirX)][(int)(data->player.posY)] == 0)
            data->player.posX += data->player.dirX * data->movespeed;
        if (worldMap[(int)(data->player.posX)][(int)(data->player.posY + data->player.dirY * 1)] == 0)
            data->player.posY += data->player.dirY * data->movespeed;
    }
    if (keycode == key_S)
    {
        if (worldMap[(int)(data->player.posX - data->player.dirX * 1)][(int)(data->player.posY)] == 0)
            data->player.posX -= data->player.dirX * data->movespeed;
        if (worldMap[(int)(data->player.posX)][(int)(data->player.posY - data->player.dirY * 1)] == 0)
            data->player.posY -= data->player.dirY * data->movespeed;
    }
}

void    rotate(int keycode, t_data *data)
{
    if (keycode == ROTATE_R)
    {
        double oldDirX = data->player.dirX;
        data->player.dirX = data->player.dirX * cos(-PI/18) - data->player.dirY * sin(-PI/18);
        data->player.dirY = oldDirX * sin(-PI/18) + data->player.dirY * cos(-PI/18);
        double oldPlaneX = data->player.planeX;
        data->player.planeX = data->player.planeX * cos(-PI/18) - data->player.planeY * sin(-PI/18);
        data->player.planeY = oldPlaneX * sin(-PI/18) + data->player.planeY * cos(-PI/18);
    }
    if (keycode == ROTATE_L)
    {
        double oldDirX = data->player.dirX;
        data->player.dirX = data->player.dirX * cos(PI/18) - data->player.dirY * sin(PI/18);
        data->player.dirY = oldDirX * sin(PI/18) + data->player.dirY * cos(PI/18);
        double oldPlaneX = data->player.planeX;
        data->player.planeX = data->player.planeX * cos(PI/18) - data->player.planeY * sin(PI/18);
        data->player.planeY = oldPlaneX * sin(PI/18) + data->player.planeY * cos(PI/18);
    }
}

int key_hook(int keycode, t_data *data)
{
    close_screen(keycode, data);
    move_r_and_l(keycode, data);
    move_f_and_b(keycode, data);
    rotate(keycode, data);
    return 0;
}

void    big_img(t_data *data)
{
    data->big_img.img = mlx_new_image(data->mlx_ptr, screenWidth, screenHeight);
    if (!data->big_img.img)
    {
        ft_error(1, "Image Error\n");
    }
    data->big_img.data = mlx_get_data_addr(data->big_img.img, &data->big_img.bits_per_pixel, &data->big_img.sizeline, &data->big_img.endian);
}

void    get_figures_datas(t_data *data)
{
    data->east.data = mlx_get_data_addr(data->east.img, &data->east.bits_per_pixel, &data->east.sizeline, &data->east.endian);
    data->north.data = mlx_get_data_addr(data->north.img, &data->north.bits_per_pixel, &data->north.sizeline, &data->north.endian);
    data->south.data = mlx_get_data_addr(data->south.img, &data->south.bits_per_pixel, &data->south.sizeline, &data->south.endian);
    data->west.data = mlx_get_data_addr(data->west.img, &data->west.bits_per_pixel, &data->west.sizeline, &data->west.endian);
}

// check this part
void    get_figures(t_data *data)
{
    int     x;
    int     y;
    data->east.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/east.xpm", &x, &y);
    data->north.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/north.xpm", &x, &y);
    data->south.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/south.xpm", &x, &y);
    data->west.img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/west.xpm", &x, &y);
    if (!(data->east.img) || !(data->north.img) || !(data->south.img) || !(data->west.img)) 
    {
        ft_error(1, "Image error\n");
        exit(1);
    }
    get_figures_datas(data);
    data->width = x;
    data->height = y;
}

void    get_color_c_and_f(t_data *data)
{
    data->ceil_color = 0x0000FF;
    data->floor_color = 0xFFFFFF;
}
void    init_data(t_data *data)
{
	data->y = 0;
    data->player.posX = 20;
    data->player.posY = 12;
    data->player.dirX = -1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.66;
    data->wall_x = 0;
    data->tex_x = 0;
    data->tex_y = 0;
    data->step = 0;
    data->tex_pos = 0;
    data->color = 0;
    data->movespeed = 0.5;
}

void    raycasting(t_data *data)
{
    mlx_loop_hook(data->mlx_ptr, draw_scene, data);
}

void    start_functions(t_data *data)
{
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, screenWidth, screenHeight, "new");
    big_img(data);
    get_color_c_and_f(data);
    get_figures(data);
    raycasting(data);
    mlx_hook(data->win_ptr, 2, 1L << 0, key_press, NULL);
    mlx_key_hook(data->win_ptr, key_hook, data);
    mlx_hook(data->win_ptr, 17, 0, close_window, NULL);
    mlx_loop(data->mlx_ptr);
}

int main()
{
    t_data *data = malloc(sizeof(t_data));
    init_data(data);
    start_functions(data);
    return 0;
}
