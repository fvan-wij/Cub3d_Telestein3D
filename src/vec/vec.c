#include <math.h>
#include <cbd_vec.h>

void	vec_normalize(t_vec2d *vec)
{
	const float	length = sqrt((vec->x * vec->x) + (vec->y * vec->y));

	vec->x = vec->x / length;
	vec->y = vec->y / length;
}

t_vec2d	vec_assign(double x, double y)
{
	t_vec2d	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec2i	vec2i(double x, double y)
{
	t_vec2i	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vec2i	vec_to_int(t_vec2d vec)
{
	t_vec2i	int_vec;

	int_vec.x = roundf(vec.x);
	int_vec.y = roundf(vec.y);
	return (int_vec);
}

t_vec2d	vec_to_float(t_vec2i vec)
{
	t_vec2d	float_vec;

	float_vec.x = (float) vec.x;
	float_vec.y = (float) vec.y;
	return (float_vec);
}
