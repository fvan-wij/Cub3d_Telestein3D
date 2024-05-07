/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 15:30:16 by dritsema      #+#    #+#                 */
/*   Updated: 2024/05/07 15:33:47 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

void	free_node(t_entity *node)
{
	if (node->destinations)
		free(node->destinations);
	if (node->texture)
		mlx_delete_texture(node->texture);
	if (node->name)
		free(node->name);
	free(node);
}

void	free_jump_table(t_map *map)
{
	int	i;

	i = 0;
	while (i < 255)
	{
		if (map->walls.w_path[i])
			free(map->walls.w_path[i]);
		i++;
	}
	i = 0;
	while (i < 255)
	{
		if (map->walls.w_tex[i])
			mlx_delete_texture(map->walls.w_tex[i]);
		i++;
	}
}
