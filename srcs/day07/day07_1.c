/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day07_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:12:24 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/07 13:12:24 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base.h"

typedef enum	s_op
{
	END = -1,
	ADD = 0,
	MUL = 1
}				t_op;

static long int	*parse_tab(char *str)
{
	long int		k;
	long int		*tab;
	long int		tab_len;
	char	*tmp;
	
	tmp = str;

	tab_len = 1;
	while (*tmp)
	{
		if (*tmp == ' ')
			tab_len++;
		tmp++;
	}
	tab = ft_calloc(sizeof(long int), tab_len + 1);
	k = -1;
	while (*str)
	{
		tab[++k] = atol(str);
		while (*str && ft_isdigit(*str))
			str++;
		while (*str && !ft_isdigit(*str))
			str++;
	}
	return (tab);
}

static long int	next_operation(t_op *ops, long int ops_length)
{
	long int	i;

	i = ops_length - 1;
	while (i >= 0)
	{
		if (ops[i] + 1 < MUL + 1)
		{
			ops[i] += 1;
			return (1);
		}
		else
			ops[i] = 0;
		i--;
	}
	ft_memset(ops, ADD, ops_length);
	return (0);
}

static long int	solve_tab(long int *tab)
{
	long int		expected = tab[0];
	long int		tab_len = -1;
	long int		result = 0;
	t_op	*ops;
	long int		i;

	tab++;
	while (tab[++tab_len]) ;
	tab_len--;
	ops = ft_calloc(sizeof(t_op), tab_len + 1);
	ops[tab_len] = -1;

	while (result != expected)
	{
		result = tab[0];
		
		i = 0;
		while (tab[++i])
		{
			if (ops[i - 1] == ADD)
				result += tab[i];
			else if (ops[i - 1] == MUL)
				result *= tab[i];
		}
		if (!next_operation(ops, tab_len) && result != expected)
			return (0);
	}

	return (expected);
}

long int	resolve_part1(char *input, char **split)
{
	(void) input;
	long int	result;
	long int	*tab;

	result = 0;
	while (*split)
	{
	
		tab = parse_tab(*split);
		for (long int i = 0; tab[i]; i++)
			printf("%ld ", tab[i]);
		printf("\n");
		result += solve_tab(tab);
		split++;
	}

	return (result);
}