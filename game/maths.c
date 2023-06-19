#include "../cub3d.h"


double	ft_degree_to_radian(double degree);
double	ft_radian_to_degree(double radian);

double	ft_degree_to_radian(double degree)
{
	double	radian;

	radian = degree * (M_PI / 180.0);
	return (radian);
}

double	ft_radian_to_degree(double radian)
{
	double degree;
    
    degree =  radian * (180.0 / M_PI);
    return (degree);
}