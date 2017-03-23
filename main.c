/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/23 16:50:27 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)**argv;
	char *test2;
	int i = 0;
	while(i < 1000)
	{
		test2 = ft_malloc(i);
		show_alloc_mem();
		i++;
	}
	test2[0] = '\0';
	/*char *test = (char *)ft_malloc(84);
	show_alloc_mem();
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
	ft_free(test);
	show_alloc_mem();
	test = (char *)ft_malloc(84);
	show_alloc_mem();
	printf("%s\n", test);
	*/return (0);
}
