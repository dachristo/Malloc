/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/13 18:46:24 by dchristo         ###   ########.fr       */
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

void		*realloc_data(void *ptr, size_t size, t_region_d *data)
{
	void 		*p;
	
	data = find_data(data, ptr);
	if (data->len > size)
	{
		data->len = size;
		data->len_left = data->len - size;
		p = data->data;
	}
	else
	{
		p = ft_malloc(size);
		ft_free(data->data);
	}
	return (p);
}

t_region_d	*find_data(t_region_d *data, void *ptr)
{
	while (data->data != ptr)
		data = data->next;
	return (data);
}

void		free_data(void *ptr, t_region_d *data, t_alloc *alloc, int region)
{
	data = find_data(data, ptr);
	if (data->data == ptr)
	{
		data->isfree = 1;
		ft_bzero(ptr, data->len);
		if (data->len_left != 0)
		{
			data->len += data->len_left;
			data->len_left = 0;
		}
		if (region == 1)
			alloc->size_tiny_used -= data->len;
		else if (region == 2)
			alloc->size_small_used -= data->len
	}
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;

	alloc = singleton();
	if (find_data(alloc->data_tiny, ptr) != NULL)
		return (realloc_data(ptr, size, alloc->data_tiny));
	else if (find_data(alloc->data_small, ptr) != NULL)
		return (realloc_data(ptr, size, alloc->data_small));
	else (realloc_data(ptr, size, alloc->data_large));
}

void		ft_free(void *ptr)
{
	t_alloc	*alloc;

	alloc = singleton();
	free_data(ptr, alloc->data_tiny, alloc, 1);
	free_data(ptr, alloc->data_small, alloc, 2);
}
