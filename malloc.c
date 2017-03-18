/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/18 16:39:44 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*ft_tiny_ptr(size_t len)
{
	t_alloc *alloc;
	alloc = singleton();
	alloc->data_tiny = new_tiny(alloc->data_tiny);
	alloc->data_tiny->len = len;
	//printf("len : %zu, %zu\n", alloc->data_tiny->len, len);
	return (alloc->data_tiny->data);
		// alloc->tiny = ft_tiny();
	//return la bonne taille de alloc->tiny;
}

void		*ft_malloc(size_t len)
{
	void	*ptr;
	
	if (len < TINY)
		return ft_tiny_ptr(len);
	else
	{
		ptr = (void *)mmap(0, len, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		return ptr;
	}
}

