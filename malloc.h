/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:47:36 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/20 22:37:49 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define M 1000000
# define TINY 4096
//# define TINY (size_t)((2*M + getpagesize()) / getpagesize())*getpagesize()
# define TINY_DATA 1024
# define SMALL 133169152
# define SMALL_DATA 127000
# include <stddef.h>
# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct			s_region_d
{
	size_t				len;
	void				*data;
	//int					isfree;
	struct s_region_d	*next;
	struct s_region_d	*prev;
}						t_region_d;

typedef struct			s_alloc
{
	struct s_region_d	*data_tiny;
	size_t				size_tiny_used;
	struct s_region_d	data_last_tiny;
	struct s_region_d	*data_small;
	struct s_region_d	data_last_small;
	struct s_region_d	*data_large;
	struct s_region_d	data_last_large;
}						t_alloc;

void					*ft_malloc(size_t len);
t_alloc					*singleton(void);
t_region_d				*new_tiny(t_region_d *data_tiny, size_t len);
t_region_d				*new_data_in_tiny(t_region_d *data_tiny, size_t len,
								t_alloc *alloc);
void					show_alloc_mem(void);
void					ft_free(void *ptr);

#endif
