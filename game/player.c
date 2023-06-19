/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:37:37 by ccestini          #+#    #+#             */
/*   Updated: 2023/04/11 12:49:39 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_set_angle(t_game *game);
double	ft_degree_to_radian(double degree);
double	ft_radian_to_degree(double radian);

void	ft_init_player(t_game *game)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
printf(" orientation= %c\n", game->map->player_orientation);
	while(game->map->map2d[i])
	{
		while (game->map->map2d[i][j])
		{
			if (game->map->map2d[i][j] == game->map->player_orientation)
				break ;
			j++;
		}
		i++;
	}
printf("player is (x, y) in 2d array (%d, %d)\n", i, j);
	game->map->map2d[i][j] = '0';
	game->p_position_x = (i * SIZE_TITLE) + (SIZE_TITLE / 2);
	game->p_position_y = (j * SIZE_TITLE) + (SIZE_TITLE / 2);
	ft_set_angle(game);
printf("radius player= %f\n", game->p_radius);
}

void	ft_set_angle(t_game *game)
{
	if (game->map->player_orientation == 'N')
		game->p_radius = ft_degree_to_radian(90);
	else if (game->map->player_orientation == 'W')
		game->p_radius = ft_degree_to_radian(180);
	else if (game->map->player_orientation == 'S')
		game->p_radius = ft_degree_to_radian(270);
	else if (game->map->player_orientation == 'E')
		game->p_radius = ft_degree_to_radian(360);
}

