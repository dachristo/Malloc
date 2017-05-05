/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:39:38 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/05 17:03:58 by dchristo         ###   ########.fr       */
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

int test_ex(void)
{
	int i = 0;

	print("test_ex\n");
	while (i < 101)
	{
		ft_malloc(1024 * 2);
		i++;
	}
	ft_malloc(1024);
	ft_malloc(1024);
	ft_malloc(1024);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 32);
	ft_malloc(1024 * 1024);
	ft_malloc(1024 * 1024);
	ft_malloc(1024 * 1024 * 1024);
	ft_malloc(1024 * 1024 * 128);
	ft_malloc(1024 * 1024 * 128);
	ft_malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}

int test5(void)
{
	print("test5\n");
	ft_malloc(1024);
	print("1 malloc");
	ft_malloc(1024 * 32);
	print("2 malloc");
	ft_malloc(1024 * 1024);
	print("3 malloc");
	ft_malloc(1024 * 1024 * 16);
	print("4 malloc");
	ft_malloc(1024 * 1024 * 128);
	print("5 malloc");
	show_alloc_mem();
	return (0);
}

int		test4(void)
{
	char *addr;

	print("test4\n");
	addr = ft_malloc(16);
	print("malloc 16\n");
	ft_free(NULL);
	print("free null\n");
	ft_free((void *)addr + 5);
	print("free malloc 16 + 5\n");
	if (ft_realloc((void *)addr + 5, 10) == NULL)
		print("realloc == null\n");
	print("realloc done\n");
	return (0);
}

int		test3bis(void)
{
	char *addr1;
	char *addr2;
	char *addr3;

	print("test3bis\n");
	addr1 = (char *)ft_malloc(16 * Mo);
	strcpy(addr1, "strcpy done 3 bis\n");
	print(addr1);
	addr2 = (char *)ft_malloc(16 * Mo);
	addr3 = (char *)ft_realloc(addr1, 128 * Mo);
	addr3[127 * Mo] = 42;
	print(addr3);
	return (0);
}

int		test3(void)
{
	char *addr1;
	char *addr3;

	print("test3\n");
	addr1 = (char *)ft_malloc(16 * Mo);
	strcpy(addr1, "strcpy done 3\n");
	print(addr1);
	addr3 = (char *)ft_realloc(addr1, 128 * Mo);
	addr3[127 * Mo] = 42;
	print(addr3);
	return (0);
}

int test2(void)
{
	char	*addr;
	int		i;

	print("test2\n");
	i = 0;
	while (i < 1024)
	{
		// addr = mmap(0, 1024, FLAGS);
		addr = (char*)ft_malloc(1024);
		addr[0] = 42;
		// munmap(addr, 1024);
		ft_free(addr);
		i++;
	}
	return (0);
}

int test1(void)
{
	char	*addr;
	int		i;

	print("test1\n");
	i = 0;
	while (i < 1024)
	{
		addr = (char*)ft_malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

int test0(void)
{
	int		i;
	print("test0\n");
	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}
/*
int	page_reclaim(FILE *pipe)
{
	char buffer[128];

	if (pipe)
	{
		while (!feof(pipe))
			if (fgets(buffer, 128, pipe) != NULL) {}
	}
	pclose(pipe);
	buffer[strlen(buffer) - 1] = 0;

	return (atoi(buffer));
}
*/
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
	}
/*	else
	{
		int t[3];

		system("export DYLD_FALLBACK_LIBRARY_PATH=.");
		system("export DYLD_INSERT_LIBRARIES=\"libft_malloc.so\"");
		system("export DYLD_FORCE_FLAT_NAMESPACE=1");
		system("./tests/print_win.sh");
		system("tput civis");
		print("Press a key to start the test.\n");
		getchar();
		print("test 0 :\n");
		system("/usr/bin/time -l ./test test0 2> test0.txt");
		system("cat test0.txt");
		FILE *pipe0 = popen("cat test0.txt | grep \"page reclaims\" | cut -d 'p' -f 1", "r");	
		t[0] = page_reclaim(pipe0);
		getchar();
		print("test 1 :\n");
		system("/usr/bin/time -l ./test test1 2> test1.txt");
		system("cat test1.txt");
		FILE *pipe1 = popen("cat test1.txt | grep \"page reclaims\" | cut -d 'p' -f 1", "r");	
		t[1] = page_reclaim(pipe1);
		getchar();
		print("test 2 :\n");
		system("/usr/bin/time -l ./test test2 2> test2.txt");
		system("cat test2.txt");
		FILE *pipe2 = popen("cat test2.txt | grep \"page reclaims\" | cut -d 'p' -f 1", "r");	
		t[2] = page_reclaim(pipe2);
		getchar();
		printf("Difference of page reclaims between test0 and test1 : %i\n\n", t[1] - t[0]);
		printf("Difference of page reclaims between test0 and test2 : %i\n\n", t[2] - t[0]);
		getchar();
		print("test 3 :\n");	
		system("./test test3");
		getchar();
		print("test 3bis :\n");
		system("./test test3bis");
		getchar();
		print("test 4 :\n");
		system("./test test4");
		getchar();
		print("test 5 :\n");
		system("./test test5");
		system("rm -rf test0.txt test1.txt test2.txt");
		system("tput cnorm");
	}
*/	return (0);
}
