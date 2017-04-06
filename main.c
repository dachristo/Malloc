/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/06 17:34:46 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)	
{
	char *test;
	/*while (argc - 1)
	{
		printf("%d\n", atoi(argv[argc - 1]));
		test = ft_malloc(atoi(argv[argc - 1]));
		(void)test;
		argc--;
		show_alloc_mem();
	}*/
	test = ft_malloc(50);
	show_alloc_mem();
	char *test2 = ft_malloc(15);
	show_alloc_mem();
	char *test3 = ft_malloc(100);
	show_alloc_mem();
	char *test4 = ft_malloc(96);
	show_alloc_mem();
	char *test5 = ft_malloc(12);
	show_alloc_mem();
	ft_free(test3);
	show_alloc_mem();
	char *test6 = ft_malloc(10);
	show_alloc_mem();
	char *test7 = ft_malloc(10);
	show_alloc_mem();
	ft_free(test7);
	show_alloc_mem();
	return (0);
}
