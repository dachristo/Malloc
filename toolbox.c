/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/19 17:49:58 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc	*singleton(void)
{
	static t_alloc alloc;
	return (&alloc);
}

t_region_d	*new_tiny(t_region_d *data_tiny, size_t len)
{
	printf("new alloc\n");
	data_tiny = (t_region_d *)mmap(0, sizeof(t_region_d) + TINY, PROT_READ |
			PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	data_tiny->len = len;
	data_tiny->data = data_tiny + sizeof(t_region_d);
	data_tiny->isfree = 0;
	data_tiny->next = NULL;
	data_tiny->prev = NULL;
	return (data_tiny);
}

t_region_d	*new_data_in_tiny(t_region_d *data_tiny, size_t len)
{
	printf("new data in tiny\n");
	while (data_tiny->next != NULL)
	{
		data_tiny = data_tiny->next;
	}
	data_tiny->next = data_tiny + sizeof(t_region_d) + data_tiny->len;
	data_tiny->next->len = len;
	data_tiny->next->data = data_tiny->next + sizeof(t_region_d);
	data_tiny->isfree = 0;
	data_tiny->next->prev = data_tiny;
	data_tiny->next->next = NULL;
	return (data_tiny->next);
}

void		show_alloc_mem(void)
{
	t_alloc *alloc;
	alloc = singleton();
	printf("ALLOC : %p\n", alloc);
	printf("TINY : %p\n", alloc->data_tiny);
	while (alloc->data_tiny != NULL)
	{
		printf("%p - %p : %zu octects\n", alloc->data_tiny->data, alloc->data_tiny->data
			   	+ alloc->data_tiny->len, alloc->data_tiny->len);
		alloc->data_tiny = alloc->data_tiny->next;
	}
}
