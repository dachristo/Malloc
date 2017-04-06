/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/06 20:03:07 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_tiny_ptr(size_t len)
{
	t_alloc		*alloc;
	
	alloc = singleton();
	if (!alloc->data_tiny)
	{
		alloc->data_tiny = new_tiny(alloc->data_tiny, len);
		alloc->size_tiny_used = alloc->data_tiny->len + sizeof(t_region_d);
		alloc->total_tiny_used = 0;
		return (alloc->data_tiny->data);
	}
	else
	{
		if ((alloc->size_tiny_used) + len > TINY - 1)
		{
			alloc->size_tiny_used = 0;
			alloc->total_tiny_used++;
			alloc->data_last_tiny = *new_tiny(&alloc->data_last_tiny, len);
			alloc->size_tiny_used = alloc->data_last_tiny.len + sizeof(t_region_d);
		}
		else
		{
			printf("new_data\n");
			alloc->data_last_tiny = *new_data_in_tiny(alloc->data_tiny, len, alloc);
		}
		return (alloc->data_last_tiny.data);
	}
}

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (size < TINY_DATA)
		ptr = ft_tiny_ptr(size);
	else
		ptr = mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
	return (ptr);
}

void		*realloc_tiny(void *ptr, size_t size, t_alloc *alloc)
{
	t_region_d 	*data_tiny;
	void 		*p;
	data_tiny = alloc->data_tiny;
	while (data_tiny->data != ptr)
	{
		data_tiny = data_tiny->next;
	}
	if (data_tiny->len > size)
	{
		data_tiny->len = size;
		data_tiny->len_left = data_tiny->len - size;
		p = data_tiny->data;
	}
	else
	{
		p = ft_malloc(size);
		ft_free(data_tiny->data);
	}
	return (p);
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
		data_tiny->isfree = 1;
		ft_bzero(ptr, data_tiny->len);
		if (data_tiny->len_left != 0)
		{
			data_tiny->len += data_tiny->len_left;
			data_tiny->len_left = 0;
		}
		alloc->size_tiny_used -= data_tiny->len;
	}
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;

	alloc = singleton();
	return (realloc_tiny(ptr, size, alloc));
	
}

void		ft_free(void *ptr)
{
	t_alloc	*alloc;

	alloc = singleton();
	free_tiny(ptr, alloc);
}
