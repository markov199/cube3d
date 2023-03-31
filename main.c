#include "cub3d.h"

void	ft_init_tmap(t_map *map, char *av[]);
int		ft_read_map_from_file(t_map *map);
int		ft_count_elements(t_map *map, char buff);
char	*ft_load_map(t_map *map);
int		ft_check_file(t_map *map);
int		ft_valid_filetype(t_map *map);
int		ft_valid_chars(t_map *map);
int		ft_valid_rectangle(t_map *map);
int		ft_valid_outer_walls(t_map *map);
int	ft_valid_inner_walls(t_map *map);
void	ft_print_2darray(char **str);
void	ft_free_2d_array(char **str);
void	ft_free_tmap(t_map *map);
int     ft_find_player_position(t_map *map);
void 	ft_make_map_rectangle(t_map *map);
int	ft_valid_rectangle(t_map *map);
int	ft_is_valid_map(t_map *map);

// cub3d functions

int	ft_get_element(char **line, t_map *map);

int	main(int ac, char *av[])
{
	t_map	map;
//	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd ("Error\nMust have one argument: Map file!\n", 2);
		exit (1);
	}
	ft_init_tmap(&map, av);
	ft_check_file(&map);

	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, (map.width * SIZE), (map.height * SIZE), "cub3d");
	// ft_init_tgame(&game);
	// game.map = &map;
	// ft_load_map_to_window(&game);
	// mlx_hook(game.win, 17, 0, &ft_end_game, &game);
	// mlx_hook(game.win, 2, 0, &ft_key_hook, &game);
	// mlx_loop(game.mlx);

	// printf("Map:\n%s\n", map.map_str);
	// printf("Map2D:\n");
	ft_print_2darray(map.map2d);
	// printf("height=%d\n", map.height);
	// printf("width=%d\n", map.width);
	// printf("len=%d\n", map.nbr_map_chars);
	// printf("player position=%d\n", map.player_position);
	// printf("player orientation=%c\n", map.player_orientation);
	// printf("len1= %ld\n", ft_strlen(map.map2d[0]));
	// printf("len4= %ld\n", ft_strlen(map.map2d[4]));
	// printf("len6= %ld\n", ft_strlen(map.map2d[6]));

	return (0);
}

void	ft_init_tmap(t_map *map, char *av[])
{
	map->filename = av[1];
	map->height = 1;
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
	map->floor_colors[0] = -1;
	map->floor_colors[1] = -1;
	map->floor_colors[2] = -1;
	map->ceiling_colors[0] = -1;
	map->ceiling_colors[1] = -1;
	map->ceiling_colors[2] = -1;
}

int	ft_read_map_from_file(t_map *map)
{
	int		fd;
	char	buff;
	int		w;
	char *line;
	int lines_read;
	int elements;

	elements = 0;
	lines_read = 0;
	w = 0;
	fd = open(map->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nMap file not found!\n", 2);
		exit (1);
	}
	while (1)
	{
		while(lines_read < 6)
		{
			line = get_next_line(fd);
			if (line == NULL)
				break;
			if (ft_strlen(line) != 0 && ++lines_read <= 6)
				elements += ft_get_element(line, map);
			free (line);
		}
		if (elements != 6)
			return (EXIT_FAILURE);
				
		if (buff != '\n')
			w++;
		if (buff == '\n')
		{
			map->height++;
			if (w > map->width)
				map->width = w;
			w = 0;
		}
		ft_count_elements(map, buff);
		map->nbr_map_chars++;
	}
	if (w > map->width)
		map->width = w;
	close(fd);
	ft_load_map(map);
	return (0);
}

int	ft_count_elements(t_map *map, char buff)
{
	if (buff == 'N' || buff == 'S' || buff == 'W' || buff == 'E')
	{
		map->count_p++;
		if (buff == 'N')
			map->player_orientation = 'N';
		else if (buff == 'S')
			map->player_orientation = 'S';
		else if (buff == 'W')
			map->player_orientation = 'W';
		else if (buff == 'E')
			map->player_orientation = 'E';
	}
	else if (buff == '0')
		map->count_0++;
	else if (buff == '1')
		map->count_1++;
	return (0);
}

char	*ft_load_map(t_map *map)
{
	int		fd;
	int		i;
	char	buff;

	i = 0;
	fd = open(map->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nMap file not found!\n", 2);
		exit (1); // change to free and exit function
	}
	map->map_str = malloc(sizeof(char) * (map->nbr_map_chars + 1));
	if (!(map->map_str))
	{
		ft_putstr_fd("Error\nNo memory allocated!\n", 2);
		exit (1);
	}
	while (read(fd, &buff, 1))
	{
		map->map_str[i] = buff;
		i++;
	}
	map->map_str[i] = '\0';
	close(fd);
	return (map->map_str);
}

void ft_make_map_rectangle(t_map *map) // to make the map rectangle
{
	char *new_map;
	int	i;
	int j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	new_map = ft_calloc(sizeof(char), (map->height * (map->width + 1)));
	while (map->map_str[i])
	{
		if (map->map_str[i] != '\n')
			new_map[j++] = map->map_str[i++];
		else if (map->map_str[i] == '\n' && len < map->width)
			new_map[j++] = ' ';
		else
		{
			new_map[j++] = map->map_str[i++];
			len = -1;
		}
		len++;
	}
	while (map->map_str[i] == '\0' && len < map->width)
	{
		new_map[j++] = ' ';
		len++;
	}
	new_map[j] = '\0';
	free(map->map_str);
	map->map_str = new_map;
	map->map2d = ft_split(map->map_str, '\n');
}

int ft_find_player_position(t_map *map)
{
    int i;

    i = 0;
    while (map->map_str[i])
    {
        if (map->map_str[i] == 'N' || map->map_str[i] == 'S' \
            || map->map_str[i] == 'W' || map->map_str[i] == 'E')
        {
			map->player_position = i;
			return (i);
        }
        i++;
    }
    return (-1);
}

int	ft_check_file(t_map *map)
{
	if (ft_valid_filetype(map) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension. Use *.cub!\n", 2);
		exit (1);
	}
	ft_read_map_from_file(map);
	ft_make_map_rectangle(map);
	ft_find_player_position(map);
	ft_is_valid_map(map);

	// do check the other elements texture and colors

	return (0);
}

int	ft_is_valid_map(t_map *map)
{
	if (ft_valid_chars(map) != 0) // check only chars accepted and one player
	{
		ft_free_tmap(map);
		exit (1);
	}
	if (ft_valid_outer_walls(map) != 0) // checking the borders of rectangle
	{
		ft_putstr_fd("Error\nMap must be surrounded by walls\n", 2);
		ft_free_tmap(map);
		exit (1);
	}
	if (ft_valid_inner_walls(map) != 0) // checking spaces inside map
	{
		ft_putstr_fd("Error\nEmpty spaces must be surrounded by walls\n", 2);
		ft_free_tmap(map);
		exit (1);
	}
	return (0);
}

int	ft_valid_filetype(t_map *map)
{
	char	*filetype;
	int		i;
	int		j;
	int		n;

	filetype = ".cub";
	n = 4;
	i = ft_strlen(map->filename) - 1;
	j = ft_strlen(filetype) -1;
	if (!map->filename || !filetype || i <= j)
		return (-1);
	while (n--)
	{
		if ((map->filename[i] == filetype[j]) && map->filename && filetype)
		{
			i--;
			j--;
		}
		else
			return (-1);
	}
	return (0);
}

int	ft_valid_chars(t_map *map)
{
	int i;

	i = -1;
	while (map->map_str[++i])
	{
		if (!(map->map_str[i] == '1' || map->map_str[i] == '0' \
			|| map->map_str[i] == '\n' || map->map_str[i] == ' ' \
			|| map->map_str[i] == 'N' || map->map_str[i] == 'S' \
			|| map->map_str[i] == 'E' || map->map_str[i] == 'W'))
		{
			ft_putstr_fd("Error\nMap with invalid character!\n", 2);
			return (-1);
		}
	}
	if (map->count_p != 1)
	{
		ft_putstr_fd("Error\nMap must have 1 Player!\n", 2);
		return (-1);
	}
	if (map->count_0 < 1) // this is not doing much
	{
		ft_putstr_fd("Error\nMap must have one or more spaces!\n", 2);
		return (-1);
	}
	return (0);
}

int	ft_valid_inner_walls(t_map *map)
{
	int		i;
	int		w;
	int		len;
	char	*s;

	i = 0;
	w = map->width + 1;
	s = map->map_str;
	len = ft_strlen(s) - 1;
	while (s[i])
	{
		if (s[i] == ' ')
		{
			if (s[i + 1] && (i + 1) >= 0 && (i + 1) <= len)
				if (!(s[i + 1] == ' ' || s[i + 1] == '1' || s[i + 1] == '\n'))
					return (-1);
			if (s[i - 1] && (i - 1) >= 0 && (i - 1) <= len)
				if (!(s[i - 1] == ' ' || s[i - 1] == '1' || s[i - 1] == '\n'))
					return (-1);
			if (s[i + w] && (i + w) >= 0 && (i + w)  <= len)
				if (!(s[i + w] == ' ' || s[i + w] == '1' || s[i + w] == '\n'))
					return (-1);
			if (s[i - w] && (i - w) >= 0 && (i - w) <= len)
				if (!(s[i - w] == ' ' || s[i - w] == '1' || s[i - w] == '\n'))
					return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_valid_outer_walls(t_map *map)
{
	int	i;
	int	n;
	int	last;

	i = 0;
	last = ft_strlen(map->map_str) -1;
	n = map->width;
	while (n-- && map->map_str[i] && map->map_str[last])
	{
		if (!(map->map_str[i] == '1' || map->map_str[i] == ' '))
			return (-1);
		if (!(map->map_str[last] == '1' || map->map_str[last] == ' '))
			return (-1);
		i++;
		last--;
	}
	i = 0;
	while (map->map_str[i])
	{
		if (map->map_str[i] == '\n' && !(map->map_str[i - 1] == '1' || map->map_str[i - 1] == ' '))
			return (-1);
		if (map->map_str[i] == '\n' && !(map->map_str[i + 1] == '1' || map->map_str[i + 1] == ' '))
			return (-1);
		i++;
	}
	return (0);
}

void	ft_print_2darray(char **str)
{
	int	i;

	i = 0;
	if (!str)
	{
		printf("(null)\n");
		return ;
	}
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	ft_free_2d_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_free_tmap(t_map *map)
{
	if (map->map_str != NULL)
		free (map->map_str);
	if (map->map2d != NULL)
		ft_free_2d_array(map->map2d);
	if (map->texture_path_north)
		free(map->texture_path_north);
	if (map->texture_path_south)
		free(map->texture_path_south);
	if (map->texture_path_west)
		free(map->texture_path_west);
	if (map->texture_path_east)
		free(map->texture_path_east);
}

int	ft_valid_rectangle(t_map *map)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (map->map_str[i])
	{
		if (map->map_str[i] != '\n')
			w++;
		if (map->map_str[i] == '\n')
		{
			if (map->width != w)
				return (-1);
			w = 0;
		}
		i++;
	}
	if (map->map_str[i] == '\0' && map->width != w)
		return (-1);
	return (0);
}

