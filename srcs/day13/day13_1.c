
#include "base.h"

typedef struct	s_pos
{
	long int	x;
	long int	y;
}				t_pos;

typedef struct	s_input
{
	t_pos		a;
	t_pos		b;
	t_pos		end;
}				t_input;

static t_input		*parse_input(char **split)
{
	t_input		*input;
	long int			y;
	long int			k;

	input = malloc(sizeof(t_input) * (1 + ft_tab_len(split) / 3));
	input[ft_tab_len(split) / 3].end.x = -1;
	input[ft_tab_len(split) / 3].end.y = -1;

	k = -1;
	y = -1;
	while (split[++y])
	{
		long int	num_len = 0;
		while (ft_isdigit(split[y][12 + num_len]))
			num_len++;
		if (y % 3 == 0)
			input[++k].a = (t_pos) {atol(split[y] + 12), atol(split[y] + 12 + num_len + 3) };
		else if (y % 3 == 1)
			input[k].b = (t_pos) {atol(split[y] + 12), atol(split[y] + 12 + num_len + 3) };
		else
		{
			num_len = 0;
			while (ft_isdigit(split[y][9 + num_len]))
				num_len++;
			input[k].end = (t_pos) {atol(split[y] + 9), atol(split[y] + 9 + num_len + 4)};
		}
	}
	return (input);
}

long int				find_min_cost(t_input input)
{
	long int		min;
	t_pos	optimal;
	t_pos	remaining;
	
	min = -1;
	for (long int A = 0; A < (input.end.x / input.a.x) + 1; A++)
	{
		remaining.x = input.end.x - A * input.a.x;
		remaining.y = input.end.y - A * input.a.y;

		if (remaining.x % input.b.x != 0 || remaining.y % input.b.y != 0)
			continue ;

		long int Bx = remaining.x / input.b.x;
		long int By = remaining.y / input.b.y;

		if (Bx == By && Bx >= 0)
		{
			long int B = Bx;

			long int cost = 3 * A + B;
			if (cost < min || min == -1)
			{
				min = cost;
				optimal.x = A;
				optimal.y = B;
			}
		}
	}
	return (min);
}

long int		resolve_part1(char *_, char **split)
{
	(void) _;
	long int		result;
	t_input	*input;

	result = 0;

	input = parse_input(split);
	for (long int i = 0; input[i].end.x != -1 && input[i].end.y != -1; i++ )
	{
		long int cost = find_min_cost(input[i]);
		if (cost > 0)
			result += cost;
	}

	return (result);
}
