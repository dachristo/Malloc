/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/11 18:34:40 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_tiny_ptr(size_t len)
{
	t_alloc		*alloc;
	
	alloc = singleton();
	if (!alloc->data_tiny)
	{
		alloc->data_tiny = new_data(alloc->data_tiny, len, TINY);
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
			alloc->data_last_tiny = *new_data(&alloc->data_last_tiny, len, TINY);
			alloc->size_tiny_used = alloc->data_last_tiny.len + sizeof(t_region_d);
		}
		else
			alloc->data_last_tiny = *new_data_in(alloc->data_tiny, len, alloc, 0);
		return (alloc->data_last_tiny.data);
	}
}

void	*ft_small_ptr(size_t len)
{
	t_alloc		*alloc;
	
	alloc = singleton();
	if (!alloc->data_small)
	{
		alloc->data_small = new_data(alloc->data_small, len, SMALL);
		alloc->size_small_used = alloc->data_small->len + sizeof(t_region_d);
		alloc->total_small_used = 0;
		return (alloc->data_small->data);
	}
	else
	{
		if ((alloc->size_small_used) + len > SMALL - 1)
		{
			alloc->size_small_used = 0;
			alloc->total_small_used++;
			alloc->data_last_small = *new_data(&alloc->data_last_small, len, SMALL);
			alloc->size_small_used = alloc->data_last_small.len + sizeof(t_region_d);
		}
		else
			alloc->data_last_small = *new_data_in(alloc->data_small, len, alloc, 1);
		return (alloc->data_last_small.data);
	}
}

void		*ft_malloc(size_t size)
{
	void	*ptr;

	if (size < TINY_DATA)
		ptr = ft_tiny_ptr(size);
	else if (size < SMALL_DATA)
		ptr = ft_small_ptr(size);
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
