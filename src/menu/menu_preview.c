#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <stdio.h>

static void	display_map_preview_a(t_menu *menu, mlx_image_t *img,
		t_map *mapdata)
{
	if (menu->select_menu.current_item == BTN_BACK)
	{
		img->instances->x = menu->preview_positions[mapdata->current_map].x;
		img->instances->y = menu->preview_positions[mapdata->current_map].y;
	}
	if (menu->select_menu.current_item == BTN_DARK_SECRET)
	{
		img->instances->x = menu->preview_positions[LVL_DARK_SECRET].x;
		img->instances->y = menu->preview_positions[LVL_DARK_SECRET].y;
		menu->current_position = menu->preview_positions[LVL_DARK_SECRET];
	}
	if (menu->select_menu.current_item == BTN_THE_BUNKER)
	{
		img->instances->x = menu->preview_positions[LVL_THE_BUNKER].x;
		img->instances->y = menu->preview_positions[LVL_THE_BUNKER].y;
		menu->current_position = menu->preview_positions[LVL_THE_BUNKER];
	}
}

static void	display_map_preview_b(t_menu *menu, mlx_image_t *img)
{
	if (menu->select_menu.current_item == BTN_RABBIT_HOLE)
	{
		img->instances->x = menu->preview_positions[LVL_RABBIT_HOLE].x;
		img->instances->y = menu->preview_positions[LVL_RABBIT_HOLE].y;
		menu->current_position = menu->preview_positions[LVL_RABBIT_HOLE];
	}
	if (menu->select_menu.current_item == BTN_SNOW_CRASH)
	{
		img->instances->x = menu->preview_positions[LVL_SNOW_CRASH].x;
		img->instances->y = menu->preview_positions[LVL_SNOW_CRASH].y;
		menu->current_position = menu->preview_positions[LVL_SNOW_CRASH];
	}
	if (menu->select_menu.current_item == BTN_CONFRONTATION)
	{
		img->instances->x = menu->preview_positions[LVL_CONFRONTATION].x;
		img->instances->y = menu->preview_positions[LVL_CONFRONTATION].y;
		menu->current_position = menu->preview_positions[LVL_CONFRONTATION];
	}
}

void	display_preview(t_menu *menu, t_map *mapdata)
{
	display_map_preview_a(menu, menu->select_menu.preview_img, mapdata);
	display_map_preview_b(menu, menu->select_menu.preview_img);
}
