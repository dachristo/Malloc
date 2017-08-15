/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:32:04 by dchristo          #+#    #+#             */
/*   Updated: 2017/08/15 18:42:03 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

static void		*realloc_data(void *ptr, size_t size, t_region_d *data)
{
	pthread_mutex_lock(ft_mutex());
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
			pthread_mutex_unlock(ft_mutex());
			ptr = malloc(size);
			if (ptr != NULL)
				ft_memcpy(ptr, data->data, data->len);
			else
				return (ptr);
			free(data->data);
			pthread_mutex_lock(ft_mutex());
		}
	}
	pthread_mutex_unlock(ft_mutex());
	if (ptr == NULL)
		ptr = malloc(size);
	else if (data == NULL)
		return (NULL);
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_alloc		*alloc;
	void		*p;

	alloc = singleton();
	if (find_data(alloc->data_tiny, ptr))
		p = realloc_data(ptr, size, alloc->data_tiny);
	else if (find_data(alloc->data_small, ptr))
		p = realloc_data(ptr, size, alloc->data_small);
	else
		p = realloc_data(ptr, size, alloc->data_large);
	return (p);
}
