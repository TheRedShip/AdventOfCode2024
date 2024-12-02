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
    char	*tmp;

	len = 0;
	while (str)

    *tab = ft_calloc(sizeof(int), ft_strlen(str));
    if (!tab)
        return (NULL);

    while (*str)
    {

        str++;
    }

}

long int	resolve_part1(char *input, char **split)
{
	(void) input;
//    int i;

    while (*split)
    {
        printf("%s\n", *split);
        split++;
    }
    return (0);
}
