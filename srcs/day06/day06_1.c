/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day06_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:17:29 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/06 23:22:22 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day01.h"

typedef enum s_dir
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
}			t_dir;

static void	get_guard_pos(char **split, int *pos)
{
	int	y;
	int	x;

	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[++x])
		{
			if (split[y][x] == '^')
			{
				pos[0] = x;
				pos[1] = y;
				pos[2] = UP;
			}
			else if (split[y][x] == 'v')
			{
				pos[0] = x;
				pos[1] = y;
				pos[2] = DOWN;
			}
			else if (split[y][x] == '>')
			{
				pos[0] = x;
				pos[1] = y;
				pos[2] = RIGHT;
			}
			if (split[y][x] == '<')
			{
				pos[0] = x;
				pos[1] = y;
				pos[2] = LEFT;
			}
		}
	}
}

static void		add_pos_dir(int *pos)
{
	if (pos[2] == UP)
		pos[1] -= 1;
	else if (pos[2] == RIGHT)
		pos[0] += 1;
	else if (pos[2] == DOWN)
		pos[1] += 1;
	else if (pos[2] == LEFT)
		pos[0] -= 1;
}

static int	not_out_of_bound(char **split, int *pos)
{
	return ((pos[0] >= 0 && pos[0] < (int)ft_strlen(split[0]) && (pos[1] >= 0 && pos[1] < (int)ft_tab_len(split))));
}

long int	resolve_part1(char *input, char **split)
{
	(void) input;
	int		result;
	int		next_pos[3];
	int		pos[3];

	result = 0;

	get_guard_pos(split, pos);

	while (not_out_of_bound(split, pos))
	{
		split[pos[1]][pos[0]] = 'X';

		next_pos[0] = pos[0];
		next_pos[1] = pos[1];
		next_pos[2] = pos[2];

		add_pos_dir(next_pos);

		if (!not_out_of_bound(split, next_pos))
			break ;

		if (split[next_pos[1]][next_pos[0]] == '#')
		{
			pos[2] += 1;
			if (pos[2] == 4)
				pos[2] = 0;
			continue ;
		}

		add_pos_dir(pos);
	}

	for(int i = 0; split[i]; i++)
	{
		for (int j = 0; split[j]; j++)
		{
			if (split[i][j] == 'X')
				result += 1;
		}
	}
	return (result);
}