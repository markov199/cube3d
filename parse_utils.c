
#include "cub3d.h"

void ft_get_element(char *line, t_map *map);

void ft_get_element(char *line, t_map *map)
{
	char **split_line;
	int i;

	i = 0;
	split_line = ft_split(line, ' ');
	if (!ft_strcmp(split_line[0], "NO "))
		map->texture_path_north = split_line[1];
	else if (!ft_strcmp(split_line[0], "SO "))
		map->texture_path_south = split_line[1];
	else if (!ft_strcmp(split_line[0], "WE "))
		map->texture_path_west = split_line[1];
	else if (!ft_strcmp(split_line[0], "EA "))
		map->texture_path_east = split_line[1];
	else if (!ft_strcmp(split_line[0], "F "))
	{
		
	}
		map->floor_colors = ft_split(split_line[i], ',');
	else if (!ft_strcmp(split_line[0], "C "))
		map->ceiling_colors = split_line[1];
}