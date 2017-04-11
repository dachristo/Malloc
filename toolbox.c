/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/11 18:52:18 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc		*singleton(void)
{
	static t_alloc alloc;

	return (&alloc);
}

t_region_d	*new_data(t_region_d *data, size_t len, size_t region)
{
	void *p;
	p = mmap(0, region, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == (void *) -1)
		return (NULL);
	data = p;
	data->data = p + sizeof(t_region_d);
	data->len = len;
	data->isfree = 0;
	data->next = NULL;
	data->prev = NULL;
	return (data);
}

t_region_d	*new_data_in_if(t_region_d* data, size_t len, t_alloc *alloc, int region)
{
	void *p;

	p = data;
	data->next = p + sizeof(t_region_d) + data->len;
	data->next->len = len;
	data->next->data = p + 2 * sizeof(t_region_d) + data->len;
	data->next->isfree = 0;
	data->next->prev = p;
	data->next->next = NULL;
	if (region == 0)
		alloc->size_tiny_used += data->next->len + sizeof(t_region_d);
	else if (region == 1)
		alloc->size_small_used += data->next->len + sizeof(t_region_d);
	return (data->next);
}

t_region_d	*new_data_in_else(t_region_d* data, size_t len, t_alloc *alloc, int region)
{
	void *p;
	void *ptr;
	
	data->isfree = 0;
	if (data->len > len + sizeof(t_region_d))
	{
		p = data->next;
		ptr = data->next->next;
		data->next = p - data->len + len;
		data->next->isfree = 1;
		data->next->len = data->len - len - sizeof(t_region_d);
		data->next->data = data->next + 1;
		data->next->prev = data;
		data->next->next = p;
		data->len = len;
		data->next->next->next = ptr;
		data->next->next->prev = data->next;
	}
	else
	{
		data->len_left = data->len - len;
		data->len = len;
	}
	if (region == 0)
		alloc->size_tiny_used += data->next->len + sizeof(t_region_d);
	else if (region == 1)
		alloc->size_small_used += data->next->len + sizeof(t_region_d);
	return (data);

}

t_region_d	*new_data_in(t_region_d *data, size_t len, t_alloc *alloc, int region)
{
	void *ptr;

	while ((data->next != NULL && data->isfree == 0) ||
			(data->isfree == 1 && data->len <= len))
	{
		printf("next %zu,  %zu, %d\n", data->len, len, data->isfree);
		data = data->next;
	}
	if (data->next == NULL || data->isfree == 0)
	{
		printf("%zu\n", data->len);
		return (new_data_in_if(data, len, alloc, region));
	}
	else
	{
		printf("is free\n");
		return (new_data_in_else(data, len, alloc, region));
	}
}

void		show_alloc_mem(void)
{
	t_alloc		*alloc;
	t_region_d	*data_tiny;

	alloc = singleton();
	data_tiny = alloc->data_tiny;
	printf("TINY : %p\n", data_tiny);
	while (data_tiny != NULL)
	{
		if (data_tiny->isfree != 2)
		{
			printf("%p - %p : %zu octects %d - %zu\n", data_tiny->data, data_tiny->data +
					data_tiny->len, data_tiny->len, data_tiny->isfree, data_tiny->len_left);
		}
		data_tiny = data_tiny->next;
	}
	printf("%zu total octects used on %lu\n", TINY * alloc->total_tiny_used + alloc->size_tiny_used, TINY + TINY * alloc->total_tiny_used);
	printf("------------------------------------------------------------\n");
}
