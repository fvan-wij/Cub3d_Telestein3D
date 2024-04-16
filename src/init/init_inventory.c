/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_inventory.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 19:25:51 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/16 20:59:31 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_inventory	*cbd_init_inventory(mlx_t *mlx)
{
	t_inventory	*inv;

	inv = ft_calloc(1, sizeof(t_inventory));
	if (!inv)
		return (NULL);
	if (!init_weapons(mlx, inv))
		return (false);
	return (inv);
}
