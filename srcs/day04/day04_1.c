
#include "day04.h"

static int	find_horizontal(char *str)
{
	if (!ft_strncmp(str, "XMAS", 4))
		return (1);
	if (!ft_strncmp(str, "SAMX", 4))
		return (1);
	return (0);
}

static int	find_vertical(char **split, int y, int x)
{
	int	i;
	int	is_verified;
	static char word[5] = {'X', 'M', 'A', 'S', 0};

	if (ft_tab_len(split) < y + 4)
		return (0);

	is_verified = 1;

	i = -1;
	while (word[++i])
	{
		if (split[y + i][x] != word[i])
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
		if (split[y + ((4 - 1) - i)][x] != word[i])
			return (0);
	}
	return (1);
}

static int	found_diagonal_down_left(char **split, int y, int x)
{
	int	i;
	int	is_verified;
	static char word[5] = {'X', 'M', 'A', 'S', 0};

	if (ft_tab_len(split) < y + 4 || (int)ft_strlen(split[y]) < x + 4)
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
		if (split[y + ((4 - 1) - i)][x + ((4 - 1) - i)] != word[i])
			return (0);
	}
	return (1);
}

static int	found_diagonal_down_right(char **split, int y, int x)
{
	int	i;
	int	is_verified;
	static char word[5] = {'X', 'M', 'A', 'S', 0};

	if (ft_tab_len(split) < y + 4 || x - 4 < 0)
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
		if (split[y + ((4 - 1) - i)][x - ((4 - 1) - i)] != word[i])
			return (0);
	}
	return (1);
}
//
//static int	found_diagonal_up_right(char **split, int y, int x)
//{
//	int	i;
//	int	is_verified;
//	static char word[5] = {'X', 'M', 'A', 'S', 0};
//
//	if (y - 4 < 0 || (int)ft_strlen(split[y]) < x + 4)
//		return (0);
//
//	is_verified = 1;
//	i = -1;
//	while (word[++i])
//	{
//		if (split[y - i][x - i] != word[i])
//		{
//			is_verified = 0;
//			break ;
//		}
//	}
//
//	if (is_verified)
//		return (1);
//
//	i = -1;
//	while (word[++i])
//	{
//		if (split[y + ((4 - 1) - i)][x + ((4 - 1) - i)] != word[i])
//			return (0);
//	}
//	return (1);
//}

long int	resolve_part1(char *input, char **split)
{
	(void) input;
	int	result;
	int	found;
	int	y;
	int	x;

	result = 0;

	y = -1;
	while (split[++y])
	{
		x = -1;
		while (split[y][++x])
		{
			found = 0;
			(void) find_horizontal(split[y] + x);
			(void) find_vertical(split, y, x);
			(void) found_diagonal_down_left(split, y, x);
			found += found_diagonal_down_right(split, y, x);
			if (found > 0)
				printf("%d %d %d\n", found, x, y);
			result += found;
		}
	}

    return (result);
}