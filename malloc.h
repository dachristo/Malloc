/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:47:36 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/15 22:23:51 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
#define TINY 4096
#define SMALL 409600
#include <stddef.h>
#include <sys/mman.h>

void	*ft_malloc(size_t len);

typedef struct	s_alloc
{
	void		*tiny;
	void		*small;
	struct s_alloc *next_tiny;
	struct s_alloc *next_small;
}				t_alloc;

#endif
