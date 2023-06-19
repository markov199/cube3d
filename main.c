/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:36:59 by ccestini          #+#    #+#             */
/*   Updated: 2023/04/11 15:05:02 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_tmap(t_map *map, char *av[]);
void	ft_init_tgame(t_game *game);

int	main(int ac, char *av[])
{
	t_map	map;
	t_game	game;
	t_mlx	mlx;
	t_image	img;
	t_point	x1;
	t_point	x2;

	if (ac != 2)
	{
		ft_putstr_fd ("Error\nMust have one argument: Map file!\n", 2);
		exit (1);
	}
	ft_init_tmap(&map, av);
	ft_check_file(&map);

	// ft_print_map_and_info(&map); // for check parsing
	game.map = &map;
	printf("orient= %c\n" , game.map->player_orientation);
	game.mlx = mlx_init();
	game.win = mlx_new_window(mlx.ptr, 1024, 512, "Drawing a line");
	img.img = mlx_new_image(mlx.ptr, 1024, 512);
	img.addr = mlx_get_data_addr(img.img, &(img.bits_per_pixel), &(img.line_len), &(img.endian));
	x1.x = 0;
	x1.y = 0;
	x2.x = 1023;
	x2.y = 511;
	ft_init_buffer(&img, 1024, 512);
	// ft_map_line(&img, x1, x2, 200);
	mlx_put_image_to_window(mlx.ptr, mlx.win, img.img, 0,0);
	mlx_key_hook(mlx.win, &key_handler, (void *)&mlx);
	mlx_loop(mlx.ptr);
	ft_free_tmap(&map);

	return (0);
}

void	ft_init_tmap(t_map *map, char *av[])
{
	map->filename = av[1];
	map->tmp_file = NULL;
	map->height = 0;
	map->width = 0;
	map->nbr_map_chars = 0;
	map->count_p = 0;
	map->count_1 = 0;
	map->count_0 = 0;
	map->player_position = -1;
	map->player_orientation = 'A';
	map->map_str = NULL;
	map->map2d = NULL;
	map->texture_path_north = NULL;
	map->texture_path_south = NULL;
	map->texture_path_west = NULL;
	map->texture_path_east = NULL;
	map->floor_rgb[0] = -1;
	map->floor_rgb[1] = -1;
	map->floor_rgb[2] = -1;
	map->ceiling_rgb[0] = -1;
	map->ceiling_rgb[1] = -1;
	map->ceiling_rgb[2] = -1;
	map->nbr_elements_file = 0;
}

