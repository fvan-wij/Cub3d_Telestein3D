/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cursor_hook.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:08:31 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:08:32 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_app	*cbd;

	cbd = (t_app *)param;
	if (cbd->state == STATE_GAME)
	{
		cbd->mouse.x = xpos;
		cbd->mouse.y = ypos;
	}
}
