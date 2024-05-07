/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   printing.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: fvan-wij <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/05/07 12:12:53 by fvan-wij      #+#    #+#                 */
/*   Updated: 2024/05/07 12:12:54 by fvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <math.h>

void	print_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s", str[i]);
		i++;
	}
}
