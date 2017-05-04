/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/05/04 17:07:03 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc		*singleton(void)
{
	static t_alloc alloc;

	return (&alloc);
}

t_region_d	*new_data(t_region_d *data, size_t len, size_t region)
{
	void *p;

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

t_region_d	*new_data_in_if(t_region_d *data, size_t len, t_alloc *alloc,
							int region)
{
	void *p;

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

t_region_d	*new_data_in_else(t_region_d *data, size_t len, t_alloc *alloc,
								int region)
{
	void *p;
	void *ptr;

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
	if (region == 0)
		alloc->size_t_used += data->next->len + sizeof(t_region_d);
	else if (region == 1)
		alloc->size_s_used += data->next->len + sizeof(t_region_d);
	return (data);
}

t_region_d	*new_data_in(t_region_d *data, size_t len, t_alloc *alloc,
						int region)
{
	while ((data->next != NULL && data->isfree == 0) ||
			(data->isfree == 1 && data->len <= len && data->next != NULL))
		data = data->next;
	if (data->next == NULL || data->isfree == 0)
		return (new_data_in_if(data, len, alloc, region));
	else
		return (new_data_in_else(data, len, alloc, region));
}

void		show_tiny_mem(t_region_d *data, t_alloc *alloc)
{
	printf("TINY : %p\n", data);
	while (data != NULL)
	{
		if (data->isfree != 2)
		{
			printf("%p - %p : %zu octects %d - %zu\n", data->data, data->data +
					data->len, data->len, data->isfree, data->len_left);
		}
		data = data->next;
	}
	printf("%zu total octects used on %lu\n", TINY * alloc->total_t_used +
			alloc->size_t_used, TINY + TINY * alloc->total_t_used);
}

void		show_small_mem(t_region_d *data, t_alloc *alloc)
{
	printf("SMALL : %p\n", data);
	while (data != NULL)
	{
		if (data->isfree != 2)
		{
			printf("%p - %p : %zu octects %d - %zu\n", data->data, data->data +
				data->len, data->len, data->isfree, data->len_left);
		}
		data = data->next;
	}
	printf("%zu total octects used on %lu\n", SMALL * alloc->total_s_used +
			alloc->size_s_used, SMALL + SMALL * alloc->total_s_used);
}

void		show_large_mem(t_region_d *data, t_alloc *alloc)
{
	printf("LARGE : %p\n", data);
	while (data != NULL)
	{
		printf("%p - %p : %zu octects %zu\n", data->data, data->data +
				data->len, data->len, data->len_left);
		data = data->next;
	}
	printf("%zu total octects used\n", alloc->size_l_used);
}

void		show_alloc_mem(void)
{
	t_alloc		*alloc;

	alloc = singleton();
	show_tiny_mem(alloc->data_tiny, alloc);
	show_small_mem(alloc->data_small, alloc);
	show_large_mem(alloc->data_large, alloc);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)str1)[i] = ((char *)str2)[i];
		i++;
	}
	return (str1);
}
