/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/04/06 17:29:36 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc		*singleton(void)
{
	static t_alloc alloc;

	return (&alloc);
}

t_region_d	*new_tiny(t_region_d *data_tiny, size_t len)
{
	void *p;
	p = mmap(0, TINY, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == (void *) -1)
		return (NULL);
	data_tiny = p;
	data_tiny->data = p + sizeof(t_region_d);
	data_tiny->len = len;
	data_tiny->isfree = 0;
	data_tiny->next = NULL;
	data_tiny->prev = NULL;
	return (data_tiny);
}

t_region_d	*new_data_in_tiny(t_region_d *data_tiny, size_t len, t_alloc *alloc)
{
	void *p;
	void *ptr;

	while ((data_tiny->next != NULL && data_tiny->isfree == 0) ||
		   	(data_tiny->isfree == 1 && data_tiny->len <= len))
	{
		printf("next %zu,  %zu, %d\n", data_tiny->len, len, data_tiny->isfree);
		data_tiny = data_tiny->next;
	}
	if (data_tiny->next == NULL || data_tiny->isfree == 0)
	{
		printf("%zu\n", data_tiny->len);
		p = data_tiny;
		data_tiny->next = p + sizeof(t_region_d) + data_tiny->len;
		data_tiny->next->len = len;
		data_tiny->next->data = p + 2 * sizeof(t_region_d) + data_tiny->len;
		data_tiny->next->isfree = 0;
		data_tiny->next->prev = p;
		data_tiny->next->next = NULL;
		alloc->size_tiny_used += data_tiny->next->len + sizeof(t_region_d);
		return (data_tiny->next);
	}
	else
	{
		printf("is free\n");
		data_tiny->isfree = 0;
		if (data_tiny->len > len + sizeof(t_region_d))
		{
			p = data_tiny->next;
			ptr = data_tiny->next->next;
			data_tiny->next = p - data_tiny->len + len;
			data_tiny->next->isfree = 1;
			data_tiny->next->len = data_tiny->len - len - sizeof(t_region_d);
			data_tiny->next->data = data_tiny->next + 1;
			data_tiny->next->prev = data_tiny;
			data_tiny->next->next = p;
			data_tiny->len = len;
			data_tiny->next->next->next = ptr;
			data_tiny->next->next->prev = data_tiny->next;
		}
		else
		{
			data_tiny->len_left = data_tiny->len - len;
			data_tiny->len = len;
		}
		alloc->size_tiny_used += len;
		return (data_tiny);
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
