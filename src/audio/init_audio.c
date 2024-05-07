/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_audio.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fvan-wij <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/07 12:07:23 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 14:28:12 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cbd_audio.h>
#include <stdlib.h>
#include <libft.h>

static ma_sound	*init_sound(ma_engine *engine, const char *path)
{
	ma_sound	*sound;
	ma_result	err;

	sound = malloc(sizeof(ma_sound));
	if (!sound)
		return (NULL);
	err = ma_sound_init_from_file(engine, path, 0, NULL, NULL, sound);
	if (err != MA_SUCCESS)
		return (NULL);
	return (sound);
}

void	cbd_uninit_audio(t_audio *audio)
{
	int	i;

	i = 0;
	ma_engine_stop(audio->engine);
	while (i < SND_SIZE)
	{
		ma_sound_uninit(audio->sound[i]);
		free(audio->sound[i]);
		i++;
	}
	ma_engine_uninit(audio->engine);
	free(audio->engine);
	free(audio);
}

static void	load_sounds_a(ma_sound *sound[SND_SIZE], ma_engine *engine)
{
	sound[SND_MUSIC] = init_sound(engine, "./data/audio/ambient_music2.mp3");
	sound[SND_WALK_GRASS] = init_sound(engine, "./data/audio/step_grass.mp3");
	sound[SND_WALK_SOLID] = init_sound(engine, "./data/audio/step_solid.mp3");
	sound[SND_MENU] = init_sound(engine, "./data/audio/menu.wav");
	sound[SND_SEARCH] = init_sound(engine, "./data/audio/search.mp3");
	sound[SND_PUNCH] = init_sound(engine, "./data/audio/punch.mp3");
	sound[SND_GUTS] = init_sound(engine, "./data/audio/guts.mp3");
	sound[SND_TAKE_DAMAGE] = init_sound(engine, "./data/audio/take_damage.mp3");
	sound[SND_NEAR_DEATH] = init_sound(engine, "./data/audio/near_death.mp3");
	sound[SND_TICK] = init_sound(engine, "./data/audio/tick.mp3");
	sound[SND_SAW] = init_sound(engine, "./data/audio/saw_loop2.mp3");
	sound[SND_SAW_IDLE] = init_sound(engine, "./data/audio/saw_idle2.mp3");
	sound[SND_WALL1] = init_sound(engine, "./data/audio/wall2.mp3");
	sound[SND_WALL2] = init_sound(engine, "./data/audio/wall3.mp3");
	sound[SND_WALL3] = init_sound(engine, "./data/audio/wall1.mp3");
	sound[SND_AMBIENT_LAUGH] = init_sound(engine, "./data/audio/a_laugh.mp3");
	sound[SND_IMPACT] = init_sound(engine, "./data/audio/impact.mp3");
	sound[SND_IMPACT2] = init_sound(engine, "./data/audio/impact2.mp3");
	sound[SND_CHASE] = init_sound(engine, "./data/audio/chase.mp3");
	sound[SND_GAME_OVER] = init_sound(engine, "./data/audio/chase_stop.mp3");
}

static void	load_sounds_b(ma_sound *sound[SND_SIZE], ma_engine *engine)
{
	sound[SND_LAUGH] = init_sound(engine, "./data/audio/laugh.mp3");
	sound[SND_NO_FUEL] = init_sound(engine, "./data/audio/no_fuel.mp3");
	sound[SND_NO_FUEL2] = init_sound(engine, "./data/audio/no_fuel2.mp3");
	sound[SND_PICKUP] = init_sound(engine, "./data/audio/item_pickup.mp3");
	sound[SND_TV_NOISE] = init_sound(engine, "./data/audio/tv_noise.mp3");
	sound[SND_TV_BYE] = init_sound(engine, "./data/audio/tv_bye.mp3");
	sound[SND_TV_JAZZ] = init_sound(engine, "./data/audio/channel2.mp3");
	sound[SND_TV_RICKROLL] = init_sound(engine, "./data/audio/channel3.mp3");
	sound[SND_TV_SURREAL] = init_sound(engine, "./data/audio/channel4.mp3");
	sound[SND_IMPACT3] = init_sound(engine, "./data/audio/impact3.mp3");
	sound[SND_CROWS] = init_sound(engine, "./data/audio/crows.mp3");
	sound[SND_BUSH] = init_sound(engine, "./data/audio/bush.mp3");
}

t_audio	*cbd_init_audio(void)
{
	t_audio		*game_audio;
	ma_result	result;

	game_audio = ft_calloc(1, sizeof(t_audio));
	if (!game_audio)
		return (NULL);
	game_audio->engine = malloc(sizeof(ma_engine));
	if (!game_audio->engine)
		return (free(game_audio), NULL);
	result = ma_engine_init(NULL, game_audio->engine);
	if (result != MA_SUCCESS)
		(free(game_audio), free(game_audio->engine), (void) NULL);
	load_sounds_a(game_audio->sound, game_audio->engine);
	load_sounds_b(game_audio->sound, game_audio->engine);
	ma_sound_set_volume(game_audio->sound[SND_MUSIC], 0.0f);
	ma_sound_set_volume(game_audio->sound[SND_WALK_SOLID], 0.6f);
	ma_sound_set_volume(game_audio->sound[SND_WALK_GRASS], 0.6f);
	ma_sound_set_volume(game_audio->sound[SND_SAW], 3.0f);
	ma_sound_set_volume(game_audio->sound[SND_SAW_IDLE], 0.6f);
	game_audio->is_initialized = true;
	return (game_audio);
}
