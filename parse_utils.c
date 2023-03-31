
#include "cub3d.h"

int ft_get_element(char *line, t_map *map);

int ft_get_element(char *line, t_map *map)
{
	char **split_line;
	char **colour_split;
	int element;
	
	element = 0;

	split_line = ft_split(line, ' ');
	if (map->texture_path_north = NULL && !ft_strcmp(split_line[0], "NO ") && ++element)
		map->texture_path_north = split_line[1];
	else if (map->texture_path_south = NULL && !ft_strcmp(split_line[0], "SO ") && ++element)
		map->texture_path_south = split_line[1];
	else if (map->texture_path_west = NULL && !ft_strcmp(split_line[0], "WE ") && ++element)
		map->texture_path_west = split_line[1];
	else if (map->texture_path_east = NULL && !ft_strcmp(split_line[0], "EA ") && ++element)
		map->texture_path_east = split_line[1];
	else if (map->floor_colour[0] = -1 && !ft_strcmp(split_line[0], "F ") && ++element)
	{
		colour_split = ft_split(split_line[[1], ',')
		map->floor_colour[0] = colour_split[0]
		map->floor_colour[1] = colour_split[1]				   
		map->floor_colour[2] = colour_split[2]			
	}
	
	else if (map->celing_colour[0] = -1 && !ft_strcmp(split_line[0], "C ") && ++element)
	{
		colour_split = ft_split(split_line[[1], ',')
		map->celing_colour[0] = colour_split[0]
		map->celing_colour[1] = colour_split[1]				   
		map->celing_colour[2] = colour_split[2]			
	}
	return (element);				
}
