#include "../cub3d.h"
// #include"./minilibx/mlx.h"
#include<unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<math.h>

t_point	x1;
t_point	x2;

int		ft_get_RGB(int red, int green, int blue);
void	my_pixel_put(t_image *img, int x, int y, int colour);
t_image	*ft_map_line(t_image *img, t_point begin, t_point end, int colour);
int		ft_init_buffer(t_image *img, int img_width, int img_height);

int	ft_get_RGB(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	my_pixel_put(t_image *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

t_image	*ft_map_line(t_image *img, t_point begin, t_point end, int colour) // add check to prevent seg fault
{
	t_point	p1;
	int		dx;
	int		dy;
	int 	sx;
	int		sy;
	int		error;
	int		e2;

	p1.x = (int)begin.x;
	p1.y = (int)begin.y;
	dx = fabs((int)end.x - p1.x);
	if (begin.x < end.x)
		sx = 1;
	else
		sx = -1;
	dy = -fabs((int)end.y - p1.y);
	printf("here\n");
	if (begin.y < end.y)
		sy = 1;
	else
		sy = -1;
	error = dx + dy;
	while (1)
	{
		my_pixel_put(img, (int)p1.x, (int)p1.y, colour);
		if (p1.x == (int)end.x && p1.y == (int)end.y)	
			break ;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (p1.x == (int)end.x)
				break ;
			error = error + dy;
			p1.x +=sx;
		}
		if (e2 <= dx)
		{
			if (p1.y == (int)end.y)
				break ;
			error = error + dx;
			p1.y +=sy;
		}
	}
	return (img);
}

int key_handler(int keycode, t_mlx *mlx)
{	
	
	// w = 13, s a = 0 , s = 1, d = 2
	if (keycode == 13)
		x1.y -= 50;
	else if (keycode == 0)
		x1.x -= 50;
	if (keycode == 1)
		x1.y += 50;
	if (keycode == 2)
		x1.x += 50;
	if (keycode == 123)
		printf("left key\n");
	if (keycode == 124)
		printf("right key\n");
	if (keycode == 53 || keycode == 12) // esc/ 'Q key  
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		exit (0);
	}
	return (0);
}

int		ft_init_buffer(t_image *img, int img_width, int img_height)
{
	int	x;
	int	y;
	t_player plyr;
	t_point	x2;


	x = 0;
	y = 0;
	
	plyr.position.x = img_width / 2;
	plyr.position.y = img_height / 2;
	plyr.view_angle = 0.01745 * 260;
	x2.x = plyr.position.x + 200 * cos(plyr.view_angle) ;
	x2.y = plyr.position.y - 200 * sin(plyr.view_angle) ;
	while (y < img_height - 1)
	{ 
		x = 0;
		while (x < img_width - 1)
		{
			if (y < img_height >> 1)
				my_pixel_put(img, x, y, 0xbfefff);
			else
				my_pixel_put(img, x, y, 0xcd66);
			x++;
		}
		y++;
	}
	printf("x %f, y %f\n plyr x %f, plyr y %f\n",x2.x, x2.y, plyr.position.x, plyr.position.y);
	ft_map_line(img, plyr.position, x2, 200);
	return (0);
}
