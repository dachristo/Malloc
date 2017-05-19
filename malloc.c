/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 21:38:26 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/19 16:19:02 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region_d	*find_data(t_region_d *data, void *ptr)
{
	if (data != NULL)
	{
		while (data != NULL && data->data != ptr)
			data = data->next;	
	}
	return (data);
}

void		*ft_tiny_ptr(size_t len)
{
	t_alloc		*alloc;

	alloc = singleton();
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

void		*ft_small_ptr(size_t len)
{
	t_alloc		*alloc;

	alloc = singleton();
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

void		*ft_large_ptr(size_t len)
{
	t_alloc		*alloc;
	t_region_d 	*data;

	alloc = singleton();
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

void		*malloc(size_t size)
{
	void	*ptr;
	
	if (size <= TINY_DATA)
		ptr = ft_tiny_ptr(size);
	else if (size <= SMALL_DATA)
		ptr = ft_small_ptr(size);
	else
		ptr = ft_large_ptr(size);
	return (ptr);
}

void		free_data(void *ptr, t_region_d *data, t_alloc *alloc, int region)
{
	data = find_data(data, ptr);
	if (data != NULL)
	{
		data->isfree = 1;
		//ft_bzero(data->data, data->len);
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

void		free_large(void *ptr, t_region_d *data, t_alloc *alloc)
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


void		free(void *ptr)
{
	t_alloc	*alloc;

	alloc = singleton();
	if (find_data(alloc->data_tiny, ptr))
		free_data(ptr, alloc->data_tiny, alloc, 1);
	else if (find_data(alloc->data_small, ptr))
		free_data(ptr, alloc->data_small, alloc, 2);
	else
		free_large(ptr, alloc->data_large, alloc);
}

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
