#include <libft.h>
#include <MLX42.h>
#include <cub3d.h>
#include <cbd_error.h>
#include <cbd_audio.h>

void	destroy_wall(t_map *mapdata, const t_player *player, t_audio *audio)
{
	char	*target;

	target = &mapdata->cbd_map
	[(int)(player->pos.y + player->dir.y)]
	[(int)(player->pos.x + player->dir.x)];
	if (*target == '=')
	{
		*target = '-';
		play_sound(audio, SND_WALL2, 0.3f, 1.0f);
	}
	else if (*target == '-')
	{
		*target = '_';
		play_sound(audio, SND_WALL1, 0.3f, 1.0f);
	}
	else if (*target == '_')
	{
		*target = '0';
		play_sound(audio, SND_WALL3, 0.3f, 1.0f);
		play_sound(audio, SND_IMPACT2, 0.2f, 1.0f);
	}
}

static void	change_tv_channel(t_audio *audio, mlx_key_data_t keydata)
{
	if (audio->tv && audio->tv->distance < 1
		&& keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	{
		stop_sound(audio, (SND_TV_BYE + audio->channel));
		audio->tv->animation.current_animation++;
		if (audio->tv->animation.current_animation
			>= audio->tv->animation.n_animations)
			audio->tv->animation.current_animation = 0;
		audio->channel = audio->tv->animation.current_animation;
	}
}

void	menu_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 3.0f);
		menu_move_cursor(cbd->menudata, -1);
	}
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 3.0f);
		menu_move_cursor(cbd->menudata, 1);
	}
	if ((keydata.key == MLX_KEY_ENTER || keydata.key == MLX_KEY_SPACE)
		&& keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 1.0f);
		menu_enter(cbd->menudata);
		if (cbd->menudata->state == OFF)
		{
			cbd->state = STATE_GAME;
			mlx_set_cursor_mode(cbd->mlx, MLX_MOUSE_DISABLED);
			mlx_set_mouse_pos(cbd->mlx, cbd->prev_mouse.x, cbd->prev_mouse.y);
		}
	}
}

// Global input handling
void	app_input(mlx_key_data_t keydata, t_app *cbd, t_audio *audio)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		play_sound(audio, SND_TICK, 1.0f, 1.0f);
		set_menu_state(cbd->menudata, MAIN);
		mlx_set_cursor_mode(cbd->mlx, MLX_MOUSE_NORMAL);
		mlx_set_mouse_pos(cbd->mlx, cbd->mlx->width / 2, cbd->mlx->height / 2);
		cbd->render.img->instances[0].enabled = false;
		cbd->state = STATE_MENU;
	}
}

void	cbd_input(mlx_key_data_t keydata, void *param)
{
	t_app	*cbd;
	t_audio	*audio;

	cbd = param;
	audio = (t_audio *) cbd->audio;
	if (cbd->menudata->state == OFF)
		game_input(keydata, cbd, audio);
	else
		menu_input(keydata, cbd, audio);
	change_tv_channel(audio, keydata);
	app_input(keydata, cbd, audio);
}
