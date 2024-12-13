
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
	long int	y;
	long int	k;

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
			input[k].end.x += 10000000000000;
			input[k].end.y += 10000000000000;
		}
	}
	return (input);
}

long int	calculate(t_input input)
{
	long int	x = (input.end.y * input.b.x - input.end.x * input.b.y) / (input.a.y * input.b.x - input.a.x * input.b.y);
	long int	y = (((-input.a.x * x) + input.end.x) / input.b.x);

	if ((input.a.x * x) + (input.b.x * y) != input.end.x || (input.a.y * x) + (input.b.y * y) != input.end.y)
		return (0);

	return ((x * 3) + y);
}

long int		resolve_part2(char *_, char **split)
{
	(void)	_;
	long int	result;
	t_input		*input;

	input = parse_input(split);
	
	result = 0;

	for (int i = 0; input[i].end.x != -1; i++)
		result += calculate(input[i]);

	return (result);
}
