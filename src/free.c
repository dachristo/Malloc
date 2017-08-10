/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:28:55 by dchristo          #+#    #+#             */
/*   Updated: 2017/08/10 17:33:07 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

static void		free_data(void *ptr, t_region_d *data, t_alloc *alloc,
						int region)
{
	data = find_data(data, ptr);
	if (data != NULL)
	{
		data->isfree = 1;
		printf("---------------------------\n");
		printf("%p, %p, %p\n", data->prev ? data->prev->data : data->prev, data ? data->data : data, data->next ? data->next->data : data->next);
		printf("---------------------------\n");
		if (data->next && data->next->isfree == 1)
		{
			data->len += data->next->len + sizeof(t_region_d);
			if (data->next->len_left != 0)
				data->len += data->next->len_left;
			data->next = data->next->next;
		}
		if (data->prev && data->prev->isfree == 1)
		{
			data->prev->len += data->len + sizeof(t_region_d);
			if (data->len_left != 0)
				data->prev->len += data->len_left;
			data->next->prev = data->prev;
			data->prev->next = data->next;
		}
		if (data->len_left != 0)
		{
			data->len += data->len_left;
			data->len_left = 0;
		}
		if (region == 1)
			alloc->size_t_used -= data->len;
		else if (region == 2)
			alloc->size_s_used -= data->len;
	}
}

static void		free_large(void *ptr, t_region_d *data, t_alloc *alloc)
{
	data = find_data(data, ptr);
	if (data != NULL)
	{
		if (!data->prev)
		{
			if (data->next)
			{
				alloc->data_large = data->next;
				data->next->prev = NULL;
			}
			else
				alloc->data_large = NULL;
		}
		else
			data->prev->next = data->next;
		alloc->size_l_used -= data->len;
		munmap(data, data->len + sizeof(t_region_d));
	}
}

void			free(void *ptr)
{
	t_alloc		*alloc;

	alloc = singleton();
	if (find_data(alloc->data_tiny, ptr))
		free_data(ptr, alloc->data_tiny, alloc, 1);
	else if (find_data(alloc->data_small, ptr))
		free_data(ptr, alloc->data_small, alloc, 2);
	else
		free_large(ptr, alloc->data_large, alloc);
}
