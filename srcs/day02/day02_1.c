/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:46:35 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/01 14:46:35 by TheRed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "day01.h"

static int  *create_tab(char *str)
{
    int 	*tab;
    int		len;
    int     i;

	len = 1;
    i = -1;
	while (str[++i])
    {
        if (str[i] == ' ')
            len++;
    }
    tab = ft_calloc(sizeof(int), len + 1);
    if (!tab)
        return (NULL);
    i = 0;
    while (*str)
    {
        tab[i++] = ft_atoi(str);
        while (*str && ft_isdigit(*str))
			str++;
		while (*str && ft_isspace(*str))
			str++;
    }
    return (tab);
}

static long int    is_safe(int *tab)
{
    int i;
    int dist;
    int is_inverted;

    is_inverted = (tab[0] - tab[1]) >= 0;
    i = -1;
    while (tab[++i + 1])
    {
        if (!is_inverted)
            dist = tab[i + 1] - tab[i];
        if (is_inverted)
            dist = tab[i] - tab[i + 1];
        if (dist <= 0 || dist > 3)
            return (0);
    }
    return (1);
}

long int	resolve_part1(char *input, char **split)
{
    (void) input;
    int i;
    int result;

    i = -1;
    result = 0;
    while (*split)
    {
        int *tab = create_tab(*split);
        result += is_safe(tab);
        for (int i = 0; tab[i]; i++)
            printf("%d ", tab[i]);
        printf("\n");
        split++;
    }
    return (result);
}
