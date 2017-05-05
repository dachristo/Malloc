/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:39:38 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/05 20:02:15 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include <time.h>
# include <limits.h>
# include <stdio.h>	
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
	for (i = 0; i < len; i++)
	{
		str[i] = c;
	}
	str[i] = '\0';
	return (str);
}

int test_ex(void)
{
	char *str;
	int i = 0;

	while (i < 101)
	{
		str = ft_malloc(1024 * 2);
		write_in(str, 1024 * 2, 'a');
		i++;
	}
	str = ft_malloc(1024);
	write_in(str, 1024, 'a');
	str = ft_malloc(1024);
	write_in(str, 1024, 'a');
	str = ft_malloc(1024);
	write_in(str, 1024, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(Mo);
	write_in(str, Mo, 'a');
	str = ft_malloc(Mo);
	write_in(str, Mo, 'a');
	str = ft_malloc(Mo * 1024);
	write_in(str, Mo * 1024, 'a');
	str = ft_malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	str = ft_malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	str = ft_malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	show_alloc_mem();
	return (0);
}

int test5(void)
{
	char *str;

	str = ft_malloc(1024);
	write_in(str, 1024, 'a');
	str = ft_malloc(1024 * 32);
	write_in(str, 1024 * 32, 'a');
	str = ft_malloc(Mo);
	write_in(str, Mo, 'a');
	str = ft_malloc(Mo * 16);
	write_in(str, Mo * 16, 'a');
	str = ft_malloc(Mo * 128);
	write_in(str, Mo * 128, 'a');
	show_alloc_mem();
	return (0);
}

int		test4(void)
{
	char *addr;

	addr = ft_malloc(16);
	write_in(addr, 16, 'a');
	ft_free(NULL);
	ft_free((void *)addr + 5);
	if (ft_realloc((void *)addr + 5, 10) == NULL)
		print("realloc == null\n");
	show_alloc_mem();
	return (0);
}

int		test3bis(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char *)ft_malloc(16 * Mo);
	write_in(addr1, Mo * 16, 'a');
	strcpy(addr1, "strcpy done 3 bis\n");
	print(addr1);
	addr2 = (char *)ft_malloc(16 * Mo);
	write_in(addr2, Mo * 16, 'a');
	addr3 = (char *)ft_realloc(addr1, 128 * Mo);
	write_in(addr3, Mo * 128, 'a');
	show_alloc_mem();
	return (0);
}

int		test3(void)
{
	char *addr1;
	char *addr3;

	addr1 = (char *)ft_malloc(16 * Mo);
	write_in(addr1, Mo * 16, 'a');
	strcpy(addr1, "strcpy done 3\n");
	addr3 = (char *)ft_realloc(addr1, 128 * Mo);
	write_in(addr3, Mo * 128, 'a');
	show_alloc_mem();
	return (0);
}

int test2(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)ft_malloc(1024);
		write_in(addr, 1024, 'a');
		ft_free(addr);
		i++;
	}
	show_alloc_mem();
	return (0);
}

int test1(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)ft_malloc(1024);
		write_in(addr, 1024, 'a');
		addr = (char*)ft_realloc(addr, 2048);
		write_in(addr, 2048, 'a');
		ft_free(addr);
		i++;
	}
	show_alloc_mem();
	return (0);
}

int test0(void)
{
	char *addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char *)ft_malloc(512);
		write_in(addr, 512, 'a');
		addr = (char *)ft_realloc(addr, 1023);
		write_in(addr, 1023, 'a');
		ft_free(addr);
		i++;
	}
	show_alloc_mem();
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
		test0();
		test1();
		test2();
		test3();
		test3bis();
		test4();
		test5();
		test_ex();
	}
	return (0);
}
