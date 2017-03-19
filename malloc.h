/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:47:36 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/19 17:45:01 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
#define TINY 4194304
#define TINY_DATA 4096
#define SMALL 133169152
#define SMALL_DATA 4194304
#include <stddef.h>
#include <sys/mman.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct			s_region_d
{
	size_t				len;
	void				*data;
	int					isfree;
	struct s_region_d	*next;
	struct s_region_d	*prev;
}						t_region_d;

typedef struct			s_alloc
{
	struct s_region_d	*data_tiny;
	struct s_region_d	data_last_tiny;
	struct s_region_d	*data_small;
	struct s_region_d	data_last_small;
	struct s_region_d	*data_large;
	struct s_region_d	data_last_large;
}						t_alloc;

void		*ft_malloc(size_t len);
t_alloc		*singleton(void);
t_region_d	*new_tiny(t_region_d *data_tiny, size_t len);
t_region_d	*new_data_in_tiny(t_region_d *data_tiny, size_t len);
void		show_alloc_mem(void);

#endif
