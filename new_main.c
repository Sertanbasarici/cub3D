#include "cub3D.h"

#define TILE_SIZE 50
#define WIDTH 400
#define HEIGHT 400

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_data;
    int bits_per_pixel;
    int size_line;
    int endian;
    int x, y;

    // MLX başlat
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Chess Board");

    // Yeni bir görüntü oluştur
    img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);

    // Görüntü verilerine eriş
    img_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

    // Satranç tahtası deseni oluşturma
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            int pixel = (y * size_line) + (x * (bits_per_pixel / 8));
            int is_white_tile = ((x / TILE_SIZE) % 2 == (y / TILE_SIZE) % 2);
            if (is_white_tile)
            {
                img_data[pixel] = 0xFF;        // Blue
                img_data[pixel + 1] = 0xFF;    // Green
                img_data[pixel + 2] = 0xFF;    // Red (Beyaz kare)
            }
            else
            {
                img_data[pixel] = 0x00;        // Blue
                img_data[pixel + 1] = 0x00;    // Green
                img_data[pixel + 2] = 0x00;    // Red (Siyah kare)
            }
        }
    }

    // Görüntüyü pencereye yerleştir
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

    // Pencereyi aktif tut
    mlx_loop(mlx_ptr);

    return 0;
}
