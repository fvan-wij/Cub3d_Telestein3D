/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_menu.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 19:14:26 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/22 15:45:54 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	load_menu_images(mlx_t *mlx, t_menu	*menu)
{
	menu->main_menu.bg = cbd_init_texture_img(mlx, "./data/menu/menu_main.png");
	menu->main_menu.cursor = cbd_init_texture_img
		(mlx, "./data/menu/selector_knife.png");
	menu->select_menu.bg = cbd_init_texture_img
		(mlx, "./data/menu/menu_map_select.png");
	menu->game_over.bg = cbd_init_texture_img(mlx, "./data/menu/game_over.png");
	menu->game_won.bg = cbd_init_texture_img(mlx, "./data/menu/game_won.png");
	menu->select_menu.preview_img = cbd_init_texture_img
		(mlx, "./data/menu/map_preview.png");
	mlx_image_to_window(mlx, menu->select_menu.preview_img, 0, 0);
	mlx_image_to_window(mlx, menu->main_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->select_menu.bg, 0, 0);
	mlx_image_to_window(mlx, menu->game_over.bg, 0, 0);
	mlx_image_to_window(mlx, menu->game_won.bg, 0, 0);
	mlx_image_to_window
		(mlx, menu->main_menu.cursor, WIDTH / 2 + 64, HEIGHT / 2);
	return (true);
}

t_menu	*cbd_init_menu(mlx_t *mlx, t_map *map)
{
	t_menu	*menu;

	menu = ft_calloc(1, sizeof(t_menu));
	if (!menu)
		return (NULL);
	if (!load_menu_images(mlx, menu))
		return (NULL);
	menu->select_menu.cursor = menu->main_menu.cursor;
	menu->game_over.cursor = menu->main_menu.cursor;
	menu->game_won.cursor = menu->main_menu.cursor;
	menu->main_menu.preview_img = menu->select_menu.preview_img;
	menu->game_won.bg->instances->enabled = false;
	set_main_cursor_positions(menu);
	set_select_cursor_positions(menu);
	set_map_preview_positions(menu);
	menu->game_over.cursor_pos = vec2i_assign(WIDTH / 2 - 64, HEIGHT / 2);
	menu->game_won.cursor_pos = menu->game_over.cursor_pos;
	set_menu_state(menu, MAIN);
	menu->main_menu.preview_img->instances->x = \
	menu->preview_positions[map->current_map].x;
	menu->main_menu.preview_img->instances->y = \
	menu->preview_positions[map->current_map].y;
	return (menu);
}
