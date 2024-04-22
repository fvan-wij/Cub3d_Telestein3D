#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>

void	enable_main_menu(t_menu *menu)
{
	set_cursor(menu->main_menu.cursor, menu->main_menu.cursor_positons[0]);
	menu->state = MAIN;
	menu->main_menu.current_item = BTN_PLAY;
	menu->main_menu.bg->instances->enabled = true;
	menu->main_menu.cursor->instances->enabled = true;
	menu->select_menu.bg->instances->enabled = false;
	menu->game_over.bg->instances->enabled = false;
	menu->game_won.bg->instances->enabled = false;
	menu->main_menu.preview_img->instances->enabled = true;
}

void	enable_map_select_menu(t_menu *menu)
{
	set_cursor(menu->select_menu.cursor, menu->select_menu.cursor_positons[0]);
	menu->state = MAP_SELECT;
	menu->select_menu.current_item = BTN_DARK_SECRET;
	menu->main_menu.bg->instances->enabled = false;
	menu->game_over.bg->instances->enabled = false;
	menu->main_menu.cursor->instances->enabled = true;
	menu->select_menu.bg->instances->enabled = true;
	menu->main_menu.preview_img->instances->enabled = true;
}

void	disable_main_menu(t_menu *menu)
{
	menu->main_menu.bg->instances->enabled = false;
	menu->main_menu.cursor->instances->enabled = false;
	menu->select_menu.bg->instances->enabled = false;
	menu->select_menu.cursor->instances->enabled = false;
	menu->main_menu.preview_img->instances->enabled = false;
	menu->game_over.bg->instances->enabled = false;
	menu->state = OFF;
}

void	enable_game_over_screen(t_menu *menu)
{
	set_cursor(menu->game_over.cursor, menu->game_over.cursor_pos);
	menu->game_over.bg->instances->enabled = true;
	menu->main_menu.cursor->instances->enabled = true;
	menu->main_menu.bg->instances->enabled = false;
	menu->main_menu.cursor->instances->enabled = false;
	menu->select_menu.bg->instances->enabled = false;
	menu->select_menu.cursor->instances->enabled = false;
	menu->main_menu.preview_img->instances->enabled = false;
	menu->state = GAME_OVER;
}

void	enable_game_won_screen(t_menu *menu)
{
	set_cursor(menu->game_won.cursor, menu->game_won.cursor_pos);
	menu->game_won.bg->instances->enabled = true;
	menu->main_menu.cursor->instances->enabled = true;
	menu->main_menu.bg->instances->enabled = false;
	menu->main_menu.cursor->instances->enabled = false;
	menu->select_menu.bg->instances->enabled = false;
	menu->select_menu.cursor->instances->enabled = false;
	menu->main_menu.preview_img->instances->enabled = false;
	menu->state = GAME_WON;
}
