/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:47:36 by dchristo          #+#    #+#             */
/*   Updated: 2017/08/15 18:38:14 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define M 1000000
# define TINY (size_t)((2*M + getpagesize()) / getpagesize())*getpagesize()
# define TINY_DATA 1024
# define SMALL (size_t)((16*M + getpagesize())/getpagesize())*getpagesize()
# define SMALL_DATA 127000

# define FT_HEX "ABCDEF"

# include <stddef.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define COLOR_RESET "\x1b[0m"
# define COLOR_REV "\033[7;7m"

typedef struct			s_region_d
{
	size_t				len;
	void				*data;
	int					isfree;
	size_t				len_left;
	struct s_region_d	*next;
	struct s_region_d	*prev;
}						t_region_d;

typedef struct			s_alloc
{
	struct s_region_d	*data_tiny;
	size_t				size_t_used;
	size_t				total_t_used;
	struct s_region_d	*data_l_tiny;
	struct s_region_d	*data_small;
	size_t				size_s_used;
	size_t				total_s_used;
	struct s_region_d	*data_l_small;
	struct s_region_d	*data_large;
	size_t				size_l_used;
	struct s_region_d	data_l_large;
}						t_alloc;

t_alloc					*singleton(void);
pthread_mutex_t			*ft_mutex(void);
t_region_d				*new_data(t_region_d *data_tiny, size_t len,
								size_t region);
t_region_d				*new_data_in(t_region_d *data_tiny, size_t len,
								t_alloc *alloc, int region);
t_region_d				*find_data(t_region_d *data, void *ptr);
void					free(void *ptr);
void					ft_putstr(char *str);
void					ft_puthex(size_t n);
void					ft_putnbr(long n);
void					*ft_memcpy(void *str1, const void *str2, size_t n);
void					*malloc(size_t size);
void					show_alloc_mem(void);

#endif
