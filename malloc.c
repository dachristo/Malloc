/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/20 22:34:33 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_tiny_ptr(size_t len)
{
	t_alloc		*alloc;
	t_region_d	data_tiny;
	
	alloc = singleton();
	if (!alloc->data_tiny)
	{
		alloc->data_tiny = new_tiny(alloc->data_tiny, len);
		alloc->size_tiny_used = alloc->data_tiny->len + sizeof(t_region_d);
		return (alloc->data_tiny->data);
	}
	else
	{
		printf("%lu, %d\n", alloc->size_tiny_used, TINY);
		if ((alloc->size_tiny_used) + len > TINY)
		{
			alloc->data_last_tiny = *new_tiny(&alloc->data_last_tiny, len);
		}
		else
		{
			data_tiny = *new_data_in_tiny(alloc->data_tiny, len, alloc);
		}
		return (data_tiny.data);
	}
}

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (size)
		ptr = ft_tiny_ptr(size);
	else
		ptr = mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}

void		free_tiny(void *ptr, t_alloc *alloc)
{
	t_region_d *data_tiny;

	data_tiny = alloc->data_tiny;
	while (data_tiny->data != ptr)
	{
		data_tiny = data_tiny->next;
	}
	if (data_tiny->data == ptr)
	{
		//data_tiny->isfree = 1;
		ft_bzero(ptr, data_tiny->len);
		alloc->size_tiny_used -= data_tiny->len;
	}
}

void		ft_free(void *ptr)
{
	t_alloc	*alloc;

	alloc = singleton();
	free_tiny(ptr, alloc);
}
