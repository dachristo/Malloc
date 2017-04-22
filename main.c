/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/22 16:52:18 by dchristo         ###   ########.fr       */
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
	test7 = ft_realloc(test7, 150);
	show_alloc_mem();
	char *test8 = ft_malloc(4500);
	show_alloc_mem();
	char *test9 = ft_malloc(5100);
	show_alloc_mem();
	ft_free(test8);
	show_alloc_mem();
	ft_realloc(test9, 8500);	
	show_alloc_mem();
	char *test10 = ft_malloc(256000);
	printf("test 10 : %p\n", test10);
	show_alloc_mem();
	char *test11 = ft_malloc(512000);
	show_alloc_mem();
	ft_free(test10);
	show_alloc_mem();
	/*ft_realloc(test11, 856000);	
	show_alloc_mem();
	*/return (0);
}
