/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/23 14:26:54 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

static void		*ft_tiny_ptr(size_t len, t_alloc *alloc)
{
	if (!alloc->data_tiny)
	{
		if ((alloc->data_tiny = new_data(alloc->data_tiny, len, TINY)) == NULL)
			return (NULL);
		alloc->size_t_used = alloc->data_tiny->len + sizeof(t_region_d);
		alloc->total_t_used = 0;
		return (alloc->data_tiny->data);
	}
	else
	{
		if ((alloc->size_t_used) + len > TINY - 1)
		{
			alloc->size_t_used = 0;
			alloc->total_t_used++;
			if ((alloc->data_l_tiny = new_data(alloc->data_l_tiny, len,
							TINY)) == NULL)
				return (NULL);
			alloc->size_t_used = alloc->data_l_tiny->len + sizeof(t_region_d);
		}
		else
			alloc->data_l_tiny = new_data_in(alloc->data_tiny, len, alloc, 0);
		return (alloc->data_l_tiny->data);
	}
}

static void		*ft_small_ptr(size_t len, t_alloc *alloc)
{
	if (!alloc->data_small)
	{
		if ((alloc->data_small = new_data(alloc->data_small, len, SMALL))
				== NULL)
			return (NULL);
		alloc->size_s_used = alloc->data_small->len + sizeof(t_region_d);
		alloc->total_s_used = 0;
		return (alloc->data_small->data);
	}
	else
	{
		if ((alloc->size_s_used) + len > SMALL - 1)
		{
			alloc->size_s_used = 0;
			alloc->total_s_used++;
			if ((alloc->data_l_small = new_data(alloc->data_l_small, len,
							SMALL)) == NULL)
				return (NULL);
			alloc->size_s_used = alloc->data_l_small->len + sizeof(t_region_d);
		}
		else
			alloc->data_l_small = new_data_in(alloc->data_small, len, alloc, 1);
		return (alloc->data_l_small->data);
	}
}

static void		*ft_large_ptr(size_t len, t_alloc *alloc)
{
	t_region_d	*data;

	if (alloc->data_large == NULL)
	{
		if ((alloc->data_large = new_data(alloc->data_large, len, len +
						sizeof(t_region_d))) == NULL)
			return (NULL);
		alloc->size_l_used = alloc->data_large->len + sizeof(t_region_d);
		return (alloc->data_large->data);
	}
	else
	{
		data = alloc->data_large;
		while (data->next != NULL)
			data = data->next;
		if ((data->next = new_data(data->next, len, len + sizeof(t_region_d)))
				== NULL)
			return (NULL);
		data->next->prev = data;
		alloc->size_l_used += data->next->len + sizeof(t_region_d);
		return (data->next->data);
	}
}

void			*malloc(size_t size)
{
	void		*ptr;
	t_alloc		*alloc;

	alloc = singleton();
	if (size <= TINY_DATA)
		ptr = ft_tiny_ptr(size, alloc);
	else if (size <= SMALL_DATA)
		ptr = ft_small_ptr(size, alloc);
	else
		ptr = ft_large_ptr(size, alloc);
	return (ptr);
}
