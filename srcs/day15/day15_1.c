
#include "base.h"

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

static t_pos	get_bot(char **split)
{
	int	y;
	int	x;

	y = -1;
	while (split[++y])
	{
		x = -1;
		while(split[y][++x])
		{
			if (split[y][x] == '@')
			{
				split[y][x] = '.';
				return (t_pos) {y, x};
			}
		}
	}
	return (t_pos) {0, 0};
}

static t_pos		get_direction(char move)
{
	t_pos	direction;

	direction.x = 0;
	direction.y = 0;

	if (move == '^')
		direction.y = -1;
	else if (move == '>')
		direction.x = 1;
	else if (move == 'v')
		direction.y = 1;
	else if (move == '<')
		direction.x = -1;

	return (direction);
}

static void		move_bot(t_pos *bot, char **split, t_pos direction)
{
	t_pos	new_pos;
	t_pos	end_pos;

	new_pos = (t_pos) {bot->x + direction.x, bot->y + direction.y};

	if (split[new_pos.y][new_pos.x] == '.')
	{
		*bot = new_pos;
		return ;
	}
	if (split[new_pos.y][new_pos.x] == '#')
		return ;

	end_pos = new_pos;
	while (split[end_pos.y][end_pos.x] == 'O')
	{
		end_pos.x += direction.x;
		end_pos.y += direction.y;
	}
	
	if (split[end_pos.y][end_pos.x] == '#')
		return ;
	
	split[new_pos.y][new_pos.x] = '.';
	split[end_pos.y][end_pos.x] = 'O';

	*bot = new_pos;
}

static void		execute_moves(t_pos *bot, char **split, char *move_line)
{
	int		x;
	t_pos	direction;
	
	x = -1;
	while (move_line[++x])
	{
		direction = get_direction(move_line[x]);

		move_bot(bot, split, direction);
	}

}

static long int		calcul_result(char **split)
{
	int			y;
	int			x;
	long int	result;

	result = 0;
	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
		{
			if (split[y][x] == 'O')
				result += 100 * y + x;
		}
	}
	return (result);
}

long int		resolve_part1(char *input, char **split)
{
	(void) input;
	t_pos	bot;
	int		result;
	char	**moves;

	moves = split;
	while (**moves == '#')
		moves++;

	bot = get_bot(split);
	while (*moves)
	{
		execute_moves(&bot, split, *moves);
		moves++;
	}

	result = calcul_result(split);

	return (result);
}

