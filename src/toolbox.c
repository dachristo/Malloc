/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/23 14:27:31 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_region_d			*new_data(t_region_d *data, size_t len, size_t region)
{
	void			*p;

	p = mmap(0, region, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (p == (void *)-1)
		return (NULL);
	data = p;
	data->data = p + sizeof(t_region_d);
	data->len = len;
	data->isfree = 0;
	data->next = NULL;
	data->prev = NULL;
	return (data);
}

static t_region_d	*new_data_in_if(t_region_d *data, size_t len,
									t_alloc *alloc, int region)
{
	void			*p;

	p = data;
	data->next = p + sizeof(t_region_d) + data->len;
	data->next->len = len;
	data->next->data = p + 2 * sizeof(t_region_d) + data->len;
	data->next->isfree = 0;
	data->next->prev = p;
	data->next->next = NULL;
	if (region == 0)
		alloc->size_t_used += data->next->len + sizeof(t_region_d);
	else if (region == 1)
		alloc->size_s_used += data->next->len + sizeof(t_region_d);
	return (data->next);
}

static t_region_d	*new_data_in_else(t_region_d *data, size_t len)
{
	void			*p;
	void			*ptr;

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
	return (data);
}

t_region_d			*new_data_in(t_region_d *data, size_t len, t_alloc *alloc,
		int region)
{
	while (data->next != NULL)
	{
		if (data->isfree == 1 && data->len <= len)
			break ;
		data = data->next;
	}
	if (data->next == NULL || data->isfree == 0)
		return (new_data_in_if(data, len, alloc, region));
	else
	{
		if (region == 0)
			alloc->size_t_used += data->next->len + sizeof(t_region_d);
		else if (region == 1)
			alloc->size_s_used += data->next->len + sizeof(t_region_d);
		return (new_data_in_else(data, len));
	}
}
