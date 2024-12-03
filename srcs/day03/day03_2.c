/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day03_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:15:16 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/03 23:15:16 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day01.h"


static void	parse_instruction(char *s, int *todo)
{
	if (!ft_strncmp(s, "do()", 4))
		*todo = 1;
	if (!ft_strncmp(s, "don't()", 7))
		*todo = 0;
}

static int	parse_mul(char *s)
{
	int	x;
	int y;
	
	if (ft_strncmp(s, "mul(", 4))
		return (-1);
	s += 4;
	if (!ft_isdigit(*s))
		return (-2);
	x = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s != ',')
		return (-3);
	s++;
	y = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	if (*s != ')')
		return (-4);
	return (x * y);
}

long int	resolve_part2(char *input, char **split)
{
	(void) split;
	int	result;
	int	parsed;
	int	todo;

	todo = 1;
	result = 0;
	while (*input)
	{
		parse_instruction(input, &todo);
		parsed = parse_mul(input);
		if (parsed > 0 && todo)
			result += parsed;

		input++;
	}
    return (result);
}