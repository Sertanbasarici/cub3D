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
        data->x++;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->big_img.img, 0, 0);
    return 0;