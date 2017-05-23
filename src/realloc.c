/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:32:04 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/23 13:34:31 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

void		*realloc_data(void *ptr, size_t size, t_region_d *data)
{
	size = size == 0 ? 1 : size;
	data = find_data(data, ptr);
	if (data != NULL)
	{
		if (data->len > size)
		{
			data->len_left = data->len - size;
			data->len = size;
			ptr = data->data;
		}
		else
		{
			ptr = malloc(size);
			ft_memcpy(ptr, data->data, data->len);
			free(data->data);
		}
	}
	else if (ptr == NULL)
		ptr = malloc(size);
	else
		return (NULL);
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	t_alloc	*alloc;

	alloc = singleton();
	if (find_data(alloc->data_tiny, ptr))
		return (realloc_data(ptr, size, alloc->data_tiny));
	else if (find_data(alloc->data_small, ptr))
		return (realloc_data(ptr, size, alloc->data_small));
	else
		return (realloc_data(ptr, size, alloc->data_large));
}
