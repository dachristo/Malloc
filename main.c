/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/17 13:26:20 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>


char	*write_in(char *str, size_t len, char c)
{
	ft_putstr("before : {");
	ft_putstr(str);
	ft_putstr("}\n");	
	int i;	
	for (i = 0; i < len; i++)
	{
		str[i] = c;
		if (i == 20)
			str[i] = '\0';
	}
	str[i] = '\0';
	ft_putstr("after : {");
	ft_putstr(str);
	ft_putstr("}\n");
	return (str);
}

int main(int argc, char **argv)	
{
	char *test;
	while (argc - 1)
	{
		printf("%d\n", atoi(argv[argc - 1]));
		test = ft_malloc(atoi(argv[argc - 1]));
		(void)test;
		argc--;
		show_alloc_mem();
	}
	if ((test = ft_malloc(50)) != NULL)
		write_in(test, 50, 'a');
	char *test2 = ft_malloc(15);
	write_in(test2, 15, 'b');
	ft_free(test);
	ft_free(test2);
	char *test3 = ft_malloc(100);
	write_in(test3, 100, 'c');
	char *test4 = ft_malloc(96);
	write_in(test4, 96, 'd');
	char *test5 = ft_malloc(12);
	write_in(test5, 12, 'e');
	ft_free(test3);
	char *test6 = ft_malloc(10);
	write_in(test6, 10, 'f');
	char *test7 = ft_malloc(10);
	write_in(test7, 10, 'g');
	test7 = ft_realloc(test7, 150);
	write_in(test7, 150, 'h');
	char *test8 = ft_malloc(4500);
	write_in(test8, 4500, 'i');
	char *test9 = ft_malloc(5100);
	write_in(test9, 5100, 'j');
	ft_free(test8);
	ft_free(test9);	
	test9 = ft_malloc(8500);
	write_in(test9, 8500, 'j');
	test9 = ft_realloc(test9, 8600);	
	write_in(test9, 8500, 'k');
	char *test10 = ft_malloc(256000);
	write_in(test10, 256000, 'l');
	char *test11 = ft_malloc(512000);
	write_in(test11, 512000, 'm');
	ft_free(test10);
	test11 = ft_realloc(test11, 856000);	
	write_in(test11, 856000, 'n');
	show_alloc_mem();
	return (0);
}
