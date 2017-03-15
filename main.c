/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:37:46 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/15 21:58:21 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)**argv;
	char *test = ft_malloc(20);
	for (int i = 0; i < 20; i++)
	{
		test[i] = '*';
	}
	printf("%s\n", test);
	return (0);
}
