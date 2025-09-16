#include "../include/visualizer.h"

void	draw_line(mlx_image_t *image, t_point begin, t_point end, int color)
{
	float	delta_x;
	float	delta_y;
	float	pixel_x;
	float	pixel_y;
	int		pixels;

	delta_x = end.x - begin.x;
	delta_y = end.y - begin.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x = delta_x / pixels;
	delta_y = delta_y / pixels;
	pixel_x = begin.x;
	pixel_y = begin.y;
	while (pixels > 0)
	{
		mlx_put_pixel(image, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void	draw_line_width(mlx_image_t *image, t_point begin, t_point end, size_t width, int color)
{
	size_t i = 0;
	t_point start_x = {(int)(begin.x - width/2), begin.y};
	t_point start_y = {begin.x, (int)(begin.y - width/2)};
	t_point end_x = {(int)(end.x -width/2), end.y}; 
	t_point end_y = {end.x, (int)(end.y - width/2)}; 
	while (i < width)
	{
		draw_line(image, start_x, end_x, color);
		draw_line(image, start_y, end_y, color);
		start_x.x ++;
		end_x.x ++;
		start_y.y ++;
		end_y.y ++;
		i++;
	}
}

void	draw_circle(mlx_image_t *image, t_point center, int radius, int color)
{
	float	angle;
	float	radians;
	float	sine;
	float	cosine;
	float	increment;

	angle = 0;
	increment = 360 / (2 * 3.1415 * radius);
	while (angle < 360)
	{
		radians = angle * (3.1415 / 180);
		sine = sin(radians);
		cosine = cos(radians);
		mlx_put_pixel(image, center.x + cosine * radius, center.y + sine * radius, color);
		angle += increment;
	}
}

void	draw_fill_circle(mlx_image_t *image, t_point center, int radius, int color)
{
	float	angle;
	float	radians;
	float	sine;
	float	cosine;
	float	increment;
	t_point begin;
	t_point end;

	angle = 90;
	increment = 360 / (2 * 3.1415 * radius);
	while (angle < 270)
	{
		radians = angle * (3.1415 / 180);
		sine = sin(radians);
		cosine = cos(radians);
		begin.x = center.x + cosine * radius;
		begin.y =  center.y + sine * radius;
		end.x =  center.x - cosine * radius;
		end.y =  center.y + sine * radius;
		draw_line(image, begin, end, color);
		angle += increment;
	}
}

void	draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num, int color)
{
	int		i;

	i = 0;
	while (i < vrt_num - 1)
	{
		draw_line(img, vertices[i], vertices[i + 1], color);
		i++;
	}
	draw_line(img, vertices[vrt_num - 1], vertices[0], color);
}

void	draw_cell(mlx_image_t *img, t_point init, int size, int color)
{
	int		y;
	int		x;
	int		color2;

	color2 = 0x666666FF;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (y == 0 || x == 0)
				mlx_put_pixel(img, (int)init.x + x, (int)init.y + y, color2);
			else
				mlx_put_pixel(img, (int)init.x + x, (int)init.y + y, color);
			x++;
		}
		y++;
	}
}