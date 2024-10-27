#include "cub3D.h"

#define Width 25
#define Height 25
#define screenWidth 800
#define screenHeight 800
#define tileSize 24

typedef struct p_data
{
    double cameraX;
    double rayDirX;
    double rayDirY;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
}	player_data;

typedef struct s_data
{
	player_data	player;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_data;

int	close_window(void *param)
{
	(void)param;
	system("leaks cub3D");
	exit(0);
}

int worldMap[Width][Height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void    verLine(int x, double drawStart, double drawEnd, int color, t_data *data)
{
    for (int y = drawStart;y < drawEnd;y++)
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
    }
}

int key_hook(int keycode, void *param)
{
    t_data *data = (t_data *)param;
	double	angle = 0;
	double	pixel_x = 0;
	double	pixel_y = 0;
    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)
    {
        printf("ESC pressed, closing the window.\n");
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data->mlx_ptr);
        return 0;
    }
    if (keycode == 124)
    {
		angle = data->player.angle;
		rotate(&data->player, 10);
	}
	else if (keycode == 123)
	{
		angle = data->player.angle;
		rotate(&data->player, -10);
	}

	if (keycode == 2)
	{
		pixel_x = data->player.px;
		data->player.px++;
	}
	if (keycode == 0)
	{
		pixel_x = data->player.px;
		data->player.px--;
	}
	if (keycode == 13)
	{
        if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
            posX += dirX * moveSpeed;
        if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
            posY += dirY * moveSpeed;
	}
	if (keycode == 1)
	{
		pixel_y = data->player.py;
		data->player.py++;
	}
	clear_player(data, angle);
	draw_player(data, data->player.angle);
	return 0;
}

int main()
{
	t_data *data;
	data = malloc(sizeof(t_data));
    data->player.posX = 22;
    data->player.posY = 12;
    data->player.dirX = -1;
    data->player.dirY = 0;
    data->player.planeX = 0;
    data->player.planeY = 0.66;
    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, screenWidth, screenHeight, "New");
    for (int x = 0; x < screenWidth;x++)
    {
        data->player.cameraX = 2 * x / (double)screenWidth - 1;
        data->player.rayDirX = data->player.dirX + data->player.planeX * data->player.cameraX;
        double rayDirY = data->player.dirY + data->player.planeY * data->player.cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;
        double sideDistX;// first encounter for X axis
        double sideDistY;// first encounter for Y axis
          //length of ray from one x or y-side to next x or y-side
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabsf(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabsf(1 / rayDirY);
        double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side;
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        while (hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
            }
            else
            {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if(side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
      //Calculate height of line to draw on screen
        int lineHeight = (int)(screenHeight / perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if(drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;
        int color;
        if (worldMap[mapX][mapY] == 0)
            color = 0xFFFF00;
        else if (worldMap[mapX][mapY] == 1)
            color = 0xFF0000;
        else if (worldMap[mapX][mapY] == 2)
            color = 0xF00000;
        else if (worldMap[mapX][mapY] == 3)
            color = 0x000000;
        else
            color = 0x000FFF;
        if (side == 1)
            {color = color / 2;}
        verLine(x, drawStart, drawEnd, color, data);
    }
    mlx_key_hook(data->win_ptr, key_hook, data);
    mlx_hook(data->win_ptr, 17, 0, close_window, NULL);
    mlx_loop(data->mlx_ptr);

    return 0;
}
