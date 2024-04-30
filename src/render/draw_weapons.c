#include <cub3d.h>

void	draw_hud(t_hud *hud, t_inventory *inv)
{
	if (inv->equipped == WPN_MAP)
		hud->img[HUD_MAP]->enabled = true;
	else
		hud->img[HUD_MAP]->enabled = false;
}

void	draw_equipped_weapon(t_inventory *inv)
{
	if (inv->equipped == WPN_FIST
		&& inv->weapons[WPN_FIST].fire_animation->loop != true)
		inv->weapons[WPN_FIST].img->enabled = true;
	else
		inv->weapons[WPN_FIST].img->enabled = false;
	if (inv->equipped == WPN_CHAINSAW
		&& inv->weapons[WPN_CHAINSAW].fire_animation->loop != true)
		inv->weapons[WPN_CHAINSAW].img->enabled = true;
	else
		inv->weapons[WPN_CHAINSAW].img->enabled = false;
	if (inv->equipped == WPN_MAP
		&& inv->weapons[WPN_CHAINSAW].fire_animation->loop != true)
		inv->weapons[WPN_MAP].img->enabled = true;
	else
		inv->weapons[WPN_MAP].img->enabled = false;
}
