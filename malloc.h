/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:47:36 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/18 16:42:40 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
#define TINY 4194304
#define SMALL 133169152
#include <stddef.h>
#include <sys/mman.h>
#include <stdio.h>

typedef struct			s_region_d
{
	size_t				len;
	char				data[1];
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

void	*ft_malloc(size_t len);
t_alloc	*singleton(void);
t_region_d *new_tiny(t_region_d *data_tiny);

#endif
