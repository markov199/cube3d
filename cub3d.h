/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkovoor <mkovoor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:35:19 by ccestini          #+#    #+#             */
/*   Updated: 2023/04/11 15:03:40 by mkovoor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SIZE_TITLE 64
# define FOV 60
# define PI 60
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

typedef struct s_map
{
	char	**tmp_file;
	int		height;
	int		width;
    int     nbr_map_chars;
	int		count_p;
	int		player_position;
	// t_point	pos;
	char	player_orientation; // N(top); S(bottom); W(left); E(right)
	int		count_1;
	int		count_0;
	char	*filename;
	char	*map_str;
    char    **map2d;
    char    *texture_path_north;
    char    *texture_path_south;
    char    *texture_path_west;
    char    *texture_path_east;
    int     floor_rgb[3];
    int     ceiling_rgb[3];
	int		nbr_elements_file;
}	t_map;

typedef struct s_game
{
	t_map	*map;
	void	*mlx;
	void	*win;
	void	*img_player;	
	double	p_start_angle;
	double	p_radius;
	double	p_position_x;
	double	p_position_y;
	//double	p_move_speed;
	//double	p_rotation_angle;
	//double	p_rotation_speed;
	void	*img_black;
	int		floor_color;
	int		ceiling_color;
}	t_game;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}t_image;
typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}t_mlx;
typedef struct s_point
{
	double	x;
	double	y;
}t_point;

typedef struct s_player
{
	t_point	position;
	double		view_angle;
}t_player;

typedef struct s_raycast
{
	void	*ptr;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	t_point	postion;
}t_raycast;


/* Parte 1 - Init structs and free*/
void	ft_init_tmap(t_map *map, char *av[]);
void	ft_free_tmap(t_map *map);
void	ft_free_2d_array(char **str);

/* Parte 2 - Get Scene from cub file */
void    ft_read_file(t_map *map);
void    ft_copy_file(t_map *map);
void	ft_scan_elements(t_map *map);
int 	ft_scan_headers(t_map *map, char *line);
int		ft_open(char *filename);
int 	ft_check_line_is_map(t_map *map, char *line);
void	ft_check_nbr_elements(t_map *map, int nbr);

void	ft_load_map(t_map *map, int i);
int		ft_count_all_map_chars(t_map *map, int i);
int		ft_copy_map(t_map *map, int i);
void	ft_check_after_map(t_map *map, int i);
int		ft_count_map_contents(t_map *map);
int 	ft_find_player_position(t_map *map);
void 	ft_make_map_rectangle(t_map *map);
void	ft_fill_map_with_spaces(t_map *map, char *new_map, int len, int j);

void	ft_get_texture_no(char *line, char **strs, t_map *map);
void	ft_get_texture_so(char *line, char **strs, t_map *map);
void	ft_get_texture_we(char *line, char **strs, t_map *map);
void	ft_get_texture_ea(char *line, char **strs, t_map *map);

void	ft_get_color_f(char **strs, char *line, t_map *map);
void	ft_get_color_c(char **strs, char *line, t_map *map);
void	ft_color_exit_free(t_map *map, char *line, char **strs);
void	ft_fill_rgb_floor(t_map *map, char **strs2);
void	ft_fill_rgb_ceiling(t_map *map, char **strs2);
void	ft_check_commas(t_map *map, char *line, char **strs);

/* Parte 3 - Check Scene from cub file */
int		ft_check_file(t_map *map);

int		ft_is_valid_map(t_map *map);
int		ft_valid_file_extension(char *filename, char *filetype);
int		ft_valid_chars(t_map *map);
int		ft_valid_rectangle(t_map *map);
int		ft_valid_inner_walls(t_map *map);
int		ft_valid_outer_walls(t_map *map);
int		ft_check_emptyspace_neighbors(t_map *map, int i, int w, int len);
int		ft_walls_check_row_top_bottom(t_map *map, int i, int last);
int		ft_walls_check_column_left_right(t_map *map, int i);

int		ft_valid_texture(t_map *map, char *tex_path, char *tex_id);
int		ft_valid_color(t_map *map, int colors[], char *color_element);

/* Parte 4 - Play Game */

int		ft_get_RGB(int red, int green, int blue);
void	my_pixel_put(t_image *img, int x, int y, int colour);
t_image	*ft_map_line(t_image *img, t_point begin, t_point end, int colour);
int		ft_init_buffer(t_image *img, int img_width, int img_height);
int		key_handler(int keycode, t_mlx *mlx);

/* Parte 5 - Utils */
void	ft_print_2darray(char **str);
int	    ft_is_whitespace(char c);
int	    ft_is_empty(char *str);
void	ft_print_map_and_info(t_map *map);

char	**ft_split2(char const *s, char c);


#endif
