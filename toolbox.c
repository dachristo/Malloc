/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/20 22:37:35 by dchristo         ###   ########.fr       */
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
	data_tiny = mmap(0, TINY, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	data_tiny->len = len;
	printf("%lu\n", sizeof(int));
	data_tiny->data = data_tiny + sizeof(t_region_d);
	//data_tiny->isfree = 0;
	data_tiny->next = NULL;
	data_tiny->prev = NULL;
	return (data_tiny);
}

t_region_d	*new_data_in_tiny(t_region_d *data_tiny, size_t len, t_alloc *alloc)
{
	while ((data_tiny->next != NULL /*&& data_tiny->isfree == 0) ||
			(data_tiny->isfree == 1 && data_tiny->len > len*/))
	{
		data_tiny = data_tiny->next;
	}
	if (data_tiny->next == NULL)
	{
		data_tiny->next = data_tiny + sizeof(t_region_d) + data_tiny->len;
		data_tiny->next->len = len;
		data_tiny->next->data = data_tiny->next + sizeof(t_region_d);
		//data_tiny->next->isfree = 0;
		data_tiny->next->prev = data_tiny;
		data_tiny->next->next = NULL;
		alloc->size_tiny_used += data_tiny->next->len + sizeof(t_region_d);
		alloc->data_last_tiny = *data_tiny;
		return (data_tiny->next);
	}
	else
	{
		//data_tiny->isfree = 0;
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
	printf("TINY : %p\n", data_tiny);
	while (data_tiny != NULL)
	{
		if (/*data_tiny->isfree == 0*/1)
		{
			printf("%p - %p : %zu octects\n", data_tiny->data, data_tiny->data +
					data_tiny->len, data_tiny->len);
		}
		data_tiny = data_tiny->next;
	}
	printf("%zu total octects used on %d\n", alloc->size_tiny_used, TINY);
	printf("------------------------------------------------------------\n");
}
