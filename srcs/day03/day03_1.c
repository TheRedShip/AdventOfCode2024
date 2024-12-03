/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day03_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:14:43 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/03 23:14:43 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day01.h"

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

long int	resolve_part1(char *input, char **split)
{
	(void) split;
    int	i;
	int	result;
	int	parsed;

	result = 0;
	i = -1;
	while (input[++i])
	{
		parsed = parse_mul(input + i);
		if (parsed > 0)
			result += parsed;
	}
    return (result);
}