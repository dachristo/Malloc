/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/15 22:39:53 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*ft_malloc(size_t len)
{
	void	*ptr;
	if (len < TINY)
		return ft_tiny_ptr(len);
	else if (len < SMALL)
		// take from small
	else
	{
		ptr = (void *)mmap(0, len, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		return ptr;
	}
}

static void	*ft_tiny_ptr(size_t len)
{
	t_alloc *alloc;
	alloc = singleton();
	if (!alloc->tiny)
		alloc->tiny = ft_tiny();
	return // la bonne taille de alloc->tiny;
}

static void *ft_small_ptr(size_t len)
{
	t_alloc *alloc;
	alloc = singleton();
	if (!alloc->small)
		alloc->small = ft_small();
	return // la bonne taille de alloc->small
}

static void	*ft_tiny(void)
{
	return ((void *)ft_malloc(TINY));
}

static void	*ft_small(void)
{
	return ((void *)ft_malloc(SMALL));
}
