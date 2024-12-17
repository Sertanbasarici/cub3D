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
    print_map(data->_map_, data->size_abc);
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
        printf("%d \n", data->hit);
        if (data->_map_[data->player.mapY][data->player.mapX] == '1')
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
        data->player.cameraX = (2 * data->x) / (double)screenWidth - 1;
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
        if (data->_map_[(int)(data->player.posY + data->player.planeY)][(int)(data->player.posX + data->player.planeX)] == '0')
        {
            data->player.posX += data->player.planeX * data->movespeed;
            data->player.posY += data->player.planeY * data->movespeed;
        }
    }
    if (keycode == key_A)
    {
        if (data->_map_[(int)(data->player.posY - data->player.planeY)][(int)(data->player.posX - data->player.planeX)] == '0')
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
        if (data->_map_[(int)(data->player.posY)][(int)(data->player.posX + data->player.dirX)] == '0')
            data->player.posX += data->player.dirX * data->movespeed;
        if (data->_map_[(int)(data->player.posY + data->player.dirY * 1)][(int)(data->player.posX)] == '0')
            data->player.posY += data->player.dirY * data->movespeed;
    }
    if (keycode == key_S)
    {
        if (data->_map_[(int)(data->player.posY)][(int)(data->player.posX - data->player.dirX * 1)] == '0')
            data->player.posX -= data->player.dirX * data->movespeed;
        if (data->_map_[(int)(data->player.posY - data->player.dirY * 1)][(int)(data->player.posX)] == '0')
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

void    get_figures(t_data *data, t_map_info *map_info)
{
    int     x;
    int     y;
    printf("%s dfsaf\n", map_info->east_texture);
    data->east.img = mlx_xpm_file_to_image(data->mlx_ptr, map_info->east_texture, &x, &y);
    data->north.img = mlx_xpm_file_to_image(data->mlx_ptr, map_info->north_texture, &x, &y);
    data->south.img = mlx_xpm_file_to_image(data->mlx_ptr, map_info->south_texture, &x, &y);
    data->west.img = mlx_xpm_file_to_image(data->mlx_ptr, map_info->west_texture, &x, &y);
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
void    init_data(t_data *data, t_point *locations, t_point *size)
{
    (void)size;
	data->y = 0;
    data->player.posX = locations->x + 0.01;
    data->player.posY = locations->y + 0.01;
    data->_map_[locations->y][locations->x] = '0';
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

void    start_functions(t_data *data, t_map_info *map_info)
{
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, screenWidth, screenHeight, "new");
    big_img(data);
    get_color_c_and_f(data);
    get_figures(data, map_info);
    raycasting(data);
    mlx_hook(data->win_ptr, 2, 1L << 0, key_press, NULL);
    mlx_key_hook(data->win_ptr, key_hook, data);
    mlx_hook(data->win_ptr, 17, 0, close_window, NULL);
    mlx_loop(data->mlx_ptr);

}

void    copy_map(char **source, char ***dest, t_point size)
{
    char **new_dest;
    int i;

    i = 0;
    new_dest = malloc(sizeof(char *) * size.y + 1);
    while (i < size.y)
    {
        new_dest[i] = ft_strdup(source[i]);
        i++;
    }
    new_dest[i] = NULL;
    *(dest) = new_dest;
}

char    *adjust_path(char *str)
{
    char    *new_str;
    int     i;
    int     j;

    j = 0;
    i = -1;
    while (str[++i] == ' ');
    i += 2;
    new_str = malloc(sizeof(char) * (ft_strlen(str) - i));
    while (str[i] != '\n')
        new_str[j++] = str[i++];
    new_str[j] = '\0';
    free(str);
    return (new_str);
}

void    get_path(t_map_info *map_info)
{
    map_info->east_texture = adjust_path(map_info->east_texture);
    map_info->west_texture = adjust_path(map_info->west_texture);
    map_info->north_texture = adjust_path(map_info->north_texture);
    map_info->south_texture = adjust_path(map_info->south_texture);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Kullanım: %s <harita_dosyası>\n", argv[0]);
        return 1;
    }
    int len = ft_strlen(argv[1]);
    if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0) {
        printf("HATA: Harita dosyasının uzantısı .cub olmalı!\n");
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Dosya açma hatası\n");
        return 1;
    }
    t_data *data = malloc(sizeof(t_data));
    t_map_info map_info;
    map_info.maps = NULL;
    data->_map_ = NULL;
    t_point *size = malloc(sizeof(t_point));
    t_point *begin = malloc(sizeof(t_point));
    size->err = 0;
    char **lines = read_lines_from_file(fd);
    if (parse_and_validate_variables(lines, &map_info) == -1)
	{
        printf("Hatalı harita bilgileri!\n");
        return 1;
    }
    int fd_copy = open(argv[1], O_RDONLY);
    checkMap(fd_copy, &map_info.maps, size, &map_info);
    close(fd_copy);
    data->size_abc = size;
    find_starting_point(map_info.maps, size, begin);
    printf("%s \n", map_info.east_texture);
    printf("%s \n", map_info.west_texture);
    printf("%s \n", map_info.south_texture);
    printf("%s \n", map_info.north_texture);
    copy_map(map_info.maps, &data->_map_, *size);
    get_path(&map_info);
    flood_fill(map_info.maps, size, begin);
    init_data(data, begin, size);
    start_functions(data, &map_info);
    return 0;
}
