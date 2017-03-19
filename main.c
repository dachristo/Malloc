/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/19 21:52:34 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)**argv;
	int i = 0;
	while (i < 10000)
	{
		char *lol = ft_malloc(1000);
		(void)lol;
		i++;
	}
	i = 0;
	char *test = (char *)ft_malloc(84);
	char *test2 = (char *)ft_malloc(42);
	while(i < 42)
	{
		test2[i] = '/';
		i++;
	}
	i = 0;
	while(i < 84)
	{
		test[i] = '*';
		i++;
	}
	test[i] = '\0';
	test2[i] = '\0';
	printf("%s\n", test);
	printf("%s\n", test2);
	show_alloc_mem();
	ft_free(test);
	show_alloc_mem();
	test = (char *)ft_malloc(84);
	printf("%s\n", test);
	show_alloc_mem();
	return (0);
}
