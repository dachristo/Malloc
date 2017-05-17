/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:39:38 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/08 19:53:51 by dchristo         ###   ########.fr       */
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

char	*write_in(char *str, size_t len, char c)
{
	int i;
	/*for (i = 0; i < len; i++)
	{
		printf("%d\n", i);
		str[i] = c;
	}
	str[i] = '\0';
	*/return (str);
}

int test_ex(void)
{
	char *str;
	int i = 0;

	while (i < 101)
	{
		str = malloc(1024 * 2);
		write_in(str, 1024 * 2, 'a');
		i++;
	}
	str = malloc(1024);
	write_in(str, 1024, 'a');
	str = malloc(1024);
	write_in(str, 1024, 'a');
	str = malloc(1024);
	write_in(str, 1024, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(Mo);
	write_in(str, Mo, 'a');
	str = malloc(Mo);
	write_in(str, Mo, 'a');
	str = malloc(Mo * 1024);
	write_in(str, Mo * 1024, 'a');
	str = malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	str = malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	str = malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	return (0);
}

int test5(void)
{
	char *str;

	str = malloc(1024);
	write_in(str, 1024, 'a');
	str = malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = malloc(Mo);
	write_in(str, Mo, 'a');
	str = malloc(Mo * 16);
	write_in(str, Mo * 16, 'a');
	str = malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	return (0);
}

int		test4(void)
{
	char *addr;

	addr = malloc(16);
	write_in(addr, 16, 'a');
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
	write_in(addr1, Mo * 16, 'a');
	addr2 = (char *)malloc(16 * Mo);
	write_in(addr2, Mo * 16, 'a');
	addr3 = (char *)realloc(addr1, 128 * Mo);
	write_in(addr3, Mo * 128, 'a');
	return (0);
}

int		test3(void)
{
	char *addr1;
	char *addr3;

	addr1 = (char *)malloc(16 * Mo);
	write_in(addr1, Mo * 16, 'a');
	addr3 = (char *)realloc(addr1, 128 * Mo);
	write_in(addr3, Mo * 128, 'a');
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
		write_in(addr, 1024, 'a');
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
		write_in(addr, 1024, 'a');
		addr = (char*)realloc(addr, 2048);
		write_in(addr, 2048, 'a');
		free(addr);
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
		addr = (char *)malloc(512);
		write_in(addr, 512, 'a');
		addr = (char *)realloc(addr, 1023);
		write_in(addr, 1023, 'a');
		free(addr);
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
