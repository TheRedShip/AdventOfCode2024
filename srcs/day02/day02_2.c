/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day01_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheRed <TheRed@students.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:13:05 by TheRed            #+#    #+#             */
/*   Updated: 2024/12/01 16:13:05 by TheRed           ###   ########.fr       */
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

static int    is_safe(int *tab)
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

static int	*pop_element(int *tab, int index)
{
	int	i;
	int	tab_len;
	int	*new_tab;

	tab_len = -1;
	while (tab[++tab_len]) ;

	new_tab = ft_calloc(sizeof(int), tab_len);
	tab_len = -1;
	i = 0;
	while (tab[++tab_len])
	{
		if (tab_len == index)
			continue ;
		new_tab[i] = tab[tab_len];
		i++;
	}
	return (new_tab);
}

static int	is_really_safe(int *tab)
{
	int	i;
	int	safe;
	int	tab_len;
	int	*tmp_tab;

	safe = is_safe(tab);
	if (safe)
		return (1);
	
	tab_len = -1;
	while (tab[++tab_len]) ;
	i = -1;
	while (tab[++i])
	{
		tmp_tab = pop_element(tab, i);
		safe = is_safe(tmp_tab);
		
		free(tmp_tab);
		
		if (safe)
			return (1);
	}
	return (0);
}

long int	resolve_part2(char *input, char **split)
{
    (void) input;
    int result;
	int	*tab;
	int	safe;

    result = 0;
    while (*split)
    {
        tab = create_tab(*split);
        safe = is_really_safe(tab);
		
		result += safe;
        split++;
    }
    return (result);
}