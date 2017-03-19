/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/19 17:50:17 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)**argv;
	char *test = (char *)ft_malloc(84);
	int i = 0;
	while(i < 84)
	{
		test[i] = '*';
		i++;
	}
	test[i] = '\0';
	printf("%s\n", test);
	char *test2 = (char *)ft_malloc(42);
	i = 0;
	while(i < 42)
	{
		test2[i] = '/';
		i++;
	}
	test2[i] = '\0';
	printf("%s\n", test2);
	printf("%s\n", test);
	show_alloc_mem();
	return (0);
}
