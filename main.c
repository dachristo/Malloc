/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/18 17:34:06 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)**argv;
	char *test = (char *)ft_malloc(42);
	int i = 0;
	while(i < 42)
	{
		test[i] = '*';
		i++;
	}
	test[i] = '\0';
	printf("%s\n", test);
	while(1);
	return (0);
}
