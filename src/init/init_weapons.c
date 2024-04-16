/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_weapons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/16 20:49:33 by dritsema      #+#    #+#                 */
/*   Updated: 2024/04/16 20:59:51 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	load_frame(mlx_t *mlx, t_animation_frame *frame, char *path)
{
	frame->img = cbd_init_texture_img(mlx, path);
	if (!frame->img)
		return (false);
	mlx_image_to_window(mlx, frame->img, \
	(WIDTH / 2) - (frame->img->width / 2), \
	HEIGHT - frame->img->height - 100);
	frame->img->enabled = false;
	frame->duration = 2;
	return (true);
}

t_animation	*load_weapon_animation(mlx_t *mlx, char *path)
{
	t_animation	*animation;
	char		*temp;
	int			n;
	int			i;

	animation = ft_calloc(1, sizeof(t_animation));
	if (!path || !animation)
		return (NULL);
	n = ft_strchr_index(path, '0');
	temp = ft_strdup(path);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < MAX_FRAMES)
	{
		if (!load_frame(mlx, &animation->frames[i], temp))
			return (NULL);
		temp[n] = temp[n] + 1;
		i++;
	}
	animation->n_frames = MAX_FRAMES;
	free(temp);
	return (animation);
}

// Function to initialize the different weapon animations
bool	init_weapon_animations(mlx_t *mlx, t_weapon *wpns)
{
	wpns[WPN_FIST].use_anim = load_weapon_animation
		(mlx, "./data/textures/player/animation/fist/frame_0.png");
	if (!wpns[WPN_FIST].use_anim)
		return (false);
	wpns[WPN_CHAINSAW].use_anim = load_weapon_animation
		(mlx, "./data/textures/player/animation/chainsaw/frame_0.png");
	if (!wpns[WPN_CHAINSAW].use_anim)
		return (false);
	wpns[WPN_MAP].use_anim = ft_calloc(1, sizeof(t_animation));
	if (!wpns[WPN_MAP].use_anim)
		return (false);
	return (true);
}

// Some hardcoded stuff that in some sense really boils my blood
// (Because of the norm, no other reason <_<)
bool	init_weapons_b(mlx_t *mlx, t_inventory *inv)
{
	inv->wpns[WPN_CHAINSAW].use_anim->frames[1].img->instances->x += 150;
	inv->wpns[WPN_CHAINSAW].use_anim->frames[1].img->instances->y -= 100;
	mlx_delete_image(mlx, inv->wpns[WPN_CHAINSAW].use_anim->frames[2].img);
	inv->wpns[WPN_CHAINSAW].use_anim->frames[2] = \
	inv->wpns[WPN_CHAINSAW].use_anim->frames[0];
	inv->wpns[WPN_CHAINSAW].use_anim->reset_x = \
	inv->wpns[WPN_CHAINSAW].use_anim->frames[1].img->instances->x;
	inv->wpns[WPN_CHAINSAW].use_anim->current_x = \
	inv->wpns[WPN_CHAINSAW].use_anim->reset_x;
	inv->wpns[WPN_CHAINSAW].in_inventory = false;
	inv->wpns[WPN_MAP].in_inventory = false;
	mlx_image_to_window(mlx, inv->wpns[WPN_MAP].img, \
	(WIDTH >> 2), (HEIGHT >> 3));
	mlx_image_to_window(mlx, inv->wpns[WPN_FIST].img, \
	(WIDTH >> 1) - (inv->wpns[WPN_FIST].img->width / 2), \
	HEIGHT - (inv->wpns[WPN_FIST].img->height >> 1));
	mlx_image_to_window(mlx, inv->wpns[WPN_CHAINSAW].img, \
	(WIDTH >> 1) - (inv->wpns[WPN_CHAINSAW].img->width / 2), \
	HEIGHT - (inv->wpns[WPN_CHAINSAW].img->height * 0.8));
	inv->wpns[WPN_MAP].img->enabled = false;
	inv->wpns[WPN_FIST].img->enabled = false;
	inv->wpns[WPN_CHAINSAW].img->enabled = false;
	return (true);
}

bool	init_weapons_a(mlx_t *mlx, t_inventory *inv)
{
	t_weapon	*wpns;

	wpns = inv->wpns;
	wpns[WPN_FIST].img = cbd_init_texture_img
		(mlx, "./data/textures/player/hands2.png");
	wpns[WPN_MAP].img = cbd_init_texture_img
		(mlx, "./data/textures/player/radar4.png");
	wpns[WPN_CHAINSAW].img = cbd_init_texture_img
		(mlx, "./data/textures/player/chainsaw.png");
	wpns[WPN_FIST].type = WPN_FIST;
	wpns[WPN_CHAINSAW].type = WPN_CHAINSAW;
	if (!init_weapon_animations(mlx, wpns))
		return (false);
	return (init_weapons_b(mlx, inv));
}
