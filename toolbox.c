/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/23 16:52:33 by dchristo         ###   ########.fr       */
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
	printf("new alloc\n");
	void *p;
	p = mmap(0, TINY, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
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
	while (data_tiny->next != NULL || (data_tiny->isfree == 1 &&
				   	data_tiny->len >= len))
	{
		printf("next\n");
		data_tiny = data_tiny->next;
	}
	if (data_tiny->next == NULL)
	{
		printf("new tiny\n");
		p = data_tiny;
		data_tiny->next = p + sizeof(t_region_d) + data_tiny->len;
		data_tiny->next->len = len;
		data_tiny->next->data = p + 2 * sizeof(t_region_d) + data_tiny->len;
		data_tiny->next->isfree = 0;
		data_tiny->next->prev = p;
		data_tiny->next->next = NULL;
		alloc->size_tiny_used += data_tiny->next->len + sizeof(t_region_d);
		alloc->data_last_tiny = *data_tiny;
		return (data_tiny->next);
	}
	else
	{
		data_tiny->isfree = 0;
		alloc->size_tiny_used += data_tiny->len;
		return (data_tiny);
	}
}

void		show_alloc_mem(void)
{
	t_alloc		*alloc;
	t_region_d	*data_tiny;

	alloc = singleton();
	data_tiny = alloc->data_tiny;
	printf("ALLOC : %p\n", alloc);
	printf("TINY : %p - %p\n", data_tiny, data_tiny + TINY);
	while (data_tiny != NULL)
	{
		if (data_tiny->isfree == 0)
		{
			printf("%p - %p : %zu octects\n", data_tiny->data, data_tiny->data +
					data_tiny->len, data_tiny->len);
		}
		data_tiny = data_tiny->next;
	}
	printf("%zu total octects used on %lu\n", TINY * alloc->total_tiny_used + alloc->size_tiny_used, TINY * alloc->total_tiny_used);
	printf("------------------------------------------------------------\n");
}
