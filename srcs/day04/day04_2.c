
#include "day01.h"

static int	found_diagonal_down_right(char **split, int y, int x)
{
	int	i;
	int	is_verified;
	static char word[5] = {'M', 'A', 'S', 0};

	if (ft_tab_len(split) < y + 3 || (int)ft_strlen(split[y]) < x + 3)
		return (0);

	is_verified = 1;
	i = -1;
	while (word[++i])
	{
		if (split[y + i][x + i] != word[i])
		{
			is_verified = 0;
			break ;
		}
	}

	if (is_verified)
		return (1);

	i = -1;
	while (word[++i])
	{
		if (split[y + ((3 - 1) - i)][x + ((3 - 1) - i)] != word[i])
			return (0);
	}
	return (1);
}

static int	found_diagonal_down_left(char **split, int y, int x)
{
	int	i;
	int	is_verified;
	static char word[5] = {'M', 'A', 'S', 0};

	if (ft_tab_len(split) < y + 3 || x - 2 < 0)
		return (0);

	is_verified = 1;
	i = -1;
	while (word[++i])
	{
		if (split[y + i][x - i] != word[i])
		{
			is_verified = 0;
			break ;
		}
	}

	if (is_verified)
		return (1);

	i = -1;
	while (word[++i])
	{
		if (split[y + ((3 - 1) - i)][x - ((3 - 1) - i)] != word[i])
			return (0);
	}
	return (1);
}

static int	find_mas(char **split, int y, int x)
{
	if (found_diagonal_down_right(split, y, x) && found_diagonal_down_left(split, y, x + 2))
		return (1);
	return (0);
}

long int	resolve_part2(char *input, char **split)
{
	(void) input;
	int	result;
	int	y;
	int	x;

	result = 0;

	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
			result += find_mas(split, y, x);;
	}
    return (result);
}