/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_navigation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:09:09 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 15:42:46 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <stdlib.h>
#include <cub3d.h>
#include <stdio.h>

void	move_cursor_main_menu(t_menu *menu, int dir)
{
	const int	state = menu->main_menu.current_item + dir;

	if (state < 0)
		menu->main_menu.current_item = BTN_MAIN_COUNT - 1;
	else if (state > (BTN_MAIN_COUNT - 1))
		menu->main_menu.current_item = 0;
	else
		menu->main_menu.current_item += dir;
	set_cursor(menu->main_menu.cursor,
		menu->main_menu.cursor_positons[menu->main_menu.current_item]);
}

void	move_cursor_select_menu(t_menu *menu, int dir)
{
	const int	state = menu->select_menu.current_item + dir;

	if (state < 0)
		menu->select_menu.current_item = BTN_SELECT_COUNT - 1;
	else if (state > BTN_SELECT_COUNT - 1)
		menu->select_menu.current_item = 0;
	else
		menu->select_menu.current_item += dir;
	set_cursor(menu->select_menu.cursor,
		menu->select_menu.cursor_positons[menu->select_menu.current_item]);
}

void	menu_move_cursor(t_menu *menu, int dir)
{
	if (menu->state == MAIN)
		move_cursor_main_menu(menu, dir);
	if (menu->state == MAP_SELECT)
		move_cursor_select_menu(menu, dir);
}

void	menu_enter(t_menu *menu)
{
	if (menu->state == MAIN)
	{
		if (menu->main_menu.current_item == BTN_PLAY)
			set_menu_state(menu, OFF);
		if (menu->main_menu.current_item == BTN_MAP_SELECT)
			printf("Map select is disabled in Demo.\n");
		if (menu->main_menu.current_item == BTN_EXIT)
			set_menu_state(menu, GAME_EXIT);
	}
	else if (menu->state == MAP_SELECT)
	{
		if (menu->select_menu.current_item == BTN_BACK)
			set_menu_state(menu, MAIN);
		else
		{
			set_menu_state(menu, MAP_LOAD);
			menu->current_position = menu->preview_positions
			[menu->select_menu.current_item];
		}
	}
	else if (menu->state == GAME_WON)
		set_menu_state(menu, MAIN);
	else if (menu->state == GAME_OVER)
		set_menu_state(menu, OFF);
}
