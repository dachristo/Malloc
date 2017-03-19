/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/19 17:49:43 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*ft_tiny_ptr(size_t len)
{
	t_alloc *alloc;
	alloc = singleton();
	if (!alloc->data_tiny)
	{
		alloc->data_tiny = new_tiny(alloc->data_tiny, len);
		return (alloc->data_tiny->data);
	}
	else
	{
		alloc->data_last_tiny = *new_data_in_tiny(alloc->data_tiny, len);
		return (alloc->data_last_tiny.data);
	}
}

void		*ft_malloc(size_t size)
{
	void	*ptr;
	
	if (size < TINY_DATA)
		return ft_tiny_ptr(size);
	else
	{
		ptr = (void *)mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		return ptr;
	}
}

