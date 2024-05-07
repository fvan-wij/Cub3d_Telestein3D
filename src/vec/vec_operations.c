/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vec_operations.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:13:02 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:13:02 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cbd_vec.h>
#include <math.h>

double	vec_dot(t_vec2d a, t_vec2d b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

double	vec_length(t_vec2d vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y)));
}

double	vec_distance(t_vec2d a, t_vec2d b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

t_vec2d	vec_rotate(t_vec2d direction, double angle)
{
	t_vec2d	new;

	new.x = (direction.x * cos(angle)) - (direction.y * sin(angle));
	new.y = (direction.x * sin(angle)) + (direction.y * cos(angle));
	direction.x = new.x;
	direction.y = new.y;
	return (new);
}
