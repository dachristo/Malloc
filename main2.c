/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:39:38 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/18 18:28:25 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include <time.h>
# include <limits.h>
# include <stdio.h>	
# include <stdlib.h>	
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# define Mo (1024 * 1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int test_ex(void)
{
	char *str;
	int i = 0;

	while (i < 101)
	{
		str = malloc(1024 * 2);
		i++;
	}
	str = malloc(1024);
	str = malloc(1024);
	str = malloc(1024);
	str = malloc(1024 * 32);
	str = malloc(1024 * 32);
	str = malloc(1024 * 32);
	str = malloc(1024 * 32);
	str = malloc(1024 * 32);
	str = malloc(1024 * 32);
	str = malloc(Mo);
	str = malloc(Mo);
	str = malloc(Mo * 1024);
	str = malloc(Mo * 128);
	str = malloc(Mo * 128);
	str = malloc(Mo * 128);
	return (0);
}

int test5(void)
{
	char *str;

	str = malloc(1024);
	str = malloc(1024 * 32);
	str = malloc(Mo);
	str = malloc(Mo * 16);
	str = malloc(Mo * 128);
	return (0);
}

int		test4(void)
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("realloc == null\n");
	return (0);
}

int		test3bis(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char *)malloc(16 * Mo);
	addr2 = (char *)malloc(16 * Mo);
	addr3 = (char *)realloc(addr1, 128 * Mo);
	return (0);
}

int		test3(void)
{
	char *addr1;
	char *addr3;

	addr1 = (char *)malloc(16 * Mo);
	addr3 = (char *)realloc(addr1, 128 * Mo);
	return (0);
}

int test2(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		free(addr);
		i++;
	}
	return (0);
}

int test1(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
			addr[0] = 42;
		i++;
	}
	return (0);
}

int test0(void)
{
	char *addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{	
	if (ac == 2)
	{
		if (!strcmp(av[1], "test0"))
			test0();
		else if (!strcmp(av[1], "test1"))
			test1();
		else if (!strcmp(av[1], "test2"))
			test2();
		else if (!strcmp(av[1], "test3"))
			test3();
		else if (!strcmp(av[1], "test3bis"))
			test3bis();
		else if (!strcmp(av[1], "test4"))
			test4();
		else if (!strcmp(av[1], "test5"))
			test5();
		else if (!strcmp(av[1], "test_ex"))
			test_ex();
	}
	else
	{
		print("test0\n");
		test0();
		print("test1\n");
		test1();
		print("test2\n");
		test2();
		print("test3\n");
		test3();
		print("test3bis\n");
		test3bis();
		print("test4\n");
		test4();
		print("test5\n");
		test5();
		print("test_ex\n");
		test_ex();
		print("test_end\n");
	}
	return (0);
}
