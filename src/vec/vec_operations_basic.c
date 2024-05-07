/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vec_operations_basic.c                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:13:05 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:13:06 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cbd_vec.h>

t_vec2d	vec_sub(t_vec2d a, t_vec2d b)
{
	t_vec2d	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

t_vec2d	vec_add(t_vec2d a, t_vec2d b)
{
	t_vec2d	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_vec2d	vec_mult(t_vec2d a, float scalar)
{
	t_vec2d	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return (result);
}

t_vec2d	vec_divide(t_vec2d vec, double denominator)
{
	vec.x = vec.x / denominator;
	vec.y = vec.y / denominator;
	return (vec);
}

t_vec2i	vec_divide_int(t_vec2i vec, double denominator)
{
	if (denominator == 2)
	{
		vec.x = vec.x >> 1;
		vec.y = vec.y >> 1;
		return (vec);
	}
	vec.x = vec.x / denominator;
	vec.y = vec.y / denominator;
	return (vec);
}
