/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/26 16:29:15 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/26 16:34:10 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_hud	*cbd_init_hud(mlx_t *mlx)
{
	t_hud	*hud;

	hud = malloc(sizeof(t_hud));
	if (!hud)
		return (NULL);
	hud->img[HUD_MAP] = mlx_new_image(mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	hud->img[HUD_OVERLAY] = mlx_new_image(mlx, WIDTH, HEIGHT);
	hud->img[HUD_CRT] = mlx_new_image(mlx, WIDTH, HEIGHT);
	hud->img[HUD_PULSE] = mlx_new_image(mlx, WIDTH, HEIGHT);
	return (hud);
}

void	cbd_init_beheading(t_app *cbd)
{
	cbd->beheading.active = false;
	cbd->beheading.timer = 0;
	cbd->beheading.chainsaw_pos = vec_assign(WIDTH / 3 - 100, 0);
	cbd->beheading.target_pos = vec_assign(0, 0);
	cbd->render.po_head->enabled = false;
}
