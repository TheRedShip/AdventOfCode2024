/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day06_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:17:39 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/07 01:13:43 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

typedef enum s_dir
{
	UP = 1,
	RIGHT = 2,
	DOWN = 3,
	LEFT = 4
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

static void	trace_path(char **split)
{
	int		next_pos[3];
	int		pos[3];

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
			if (pos[2] == LEFT + 1)
				pos[2] = UP;
			continue ;
		}

		add_pos_dir(pos);
	}
}

static char	**split_dup(char **split)
{
	int	i;
	char **new_split;
	
	new_split = ft_calloc(sizeof(char *), ft_tab_len(split) + 1);
	i = -1;
	while (split[++i])
		new_split[i] = ft_strdup(split[i]);
	return (new_split);
}

static int	is_infinite_path(char **split, int x, int y, int *pos)
{
	int	next_pos[3];

	if (pos[0] == x && pos[1] == y)
	{
		free(split);
		return (0);
	}

	split[y][x] = '#';
	while (split[pos[1]][pos[0]] != pos[2])
	{
		if (split[pos[1]][pos[0]] > LEFT + 1)
			split[pos[1]][pos[0]] = pos[2];
	
		next_pos[0] = pos[0];
		next_pos[1] = pos[1];
		next_pos[2] = pos[2];

		add_pos_dir(next_pos);

		if (!not_out_of_bound(split, next_pos))
		{
			free(split);
			return (0);
		}

		if (split[next_pos[1]][next_pos[0]] == '#')
		{
			pos[2] += 1;
			if (pos[2] == LEFT + 1)
				pos[2] = UP;
			continue ;
		}
		
		add_pos_dir(pos);
	}
	ft_free_tab((void **)split);
	return (1);
}

long int	resolve_part2(char *input, char **split)
{
	(void) input;
	int	y;
	int	x;
	int	result;
	int	pos[3];
	int	pos_copy[3];
	
	get_guard_pos(split, pos);

	result = 0;
	trace_path(split);

	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[++x])
		{
			if (split[y][x] == 'X')
			{
				pos_copy[0] = pos[0];
				pos_copy[1] = pos[1];
				pos_copy[2] = pos[2];
				
				result += is_infinite_path(split_dup(split), x, y, pos_copy);
			}
		}
	}
	
	return (result);
}