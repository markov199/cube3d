#ifndef CUB3D_H
# define CUB3D_H

# define SIZE 50

//# include "./minilibx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_map
{
	int		height;
	int		width;
    int     nbr_map_chars;
	int		count_p;
	int		player_position;
	char	player_orientation; // 1-North(top); 2-South(bottom); 3-West(left); 4-East(right)
	int		count_1;
	int		count_0;
	char	*filename;
	char	*map_str;
    char    **map2d;
    char    *texture_path_north;
    char    *texture_path_south;
    char    *texture_path_west;
    char    *texture_path_east;
    int     floor_colors[3];
    int     ceiling_colors[3];
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img_p1;
	void	*img_p2;
	void	*img_c1;
	void	*img_c2;
	void	*img_s;
	void	*img_w;
	void	*img_e;
	t_map	*map;
	int		collected_c;
	int		moves;
}	t_game;


/* Parte 1 - Init structs and free allocations */
void	ft_init_tmap(t_map *map, char *av[]);


/* Parte 2 - Check Scene from cub file */
int		ft_check_file(t_map *map);


/* Parte 4 - Play Game */
void	ft_init_tgame(t_game *game);
void	ft_load_map_to_window(t_game *game);
int		ft_key_hook(int keycode, t_game *game);
void	ft_move(t_game *game, int new_position);
void	ft_load_animation(t_game *game, int x, int y, char a);
void	ft_print_moves_on_screen(t_game *game);
void	ft_end_game(t_game *game);

int ft_get_element(char *line, t_map *map);
#endif
