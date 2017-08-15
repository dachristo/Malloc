/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:31:24 by dchristo          #+#    #+#             */
/*   Updated: 2017/08/15 15:18:18 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/malloc.h"

t_alloc		*singleton(void)
{
	static	t_alloc alloc;

	return (&alloc);
}

pthread_mutex_t		*ft_mutex(void)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	return (mutex);
}

t_region_d	*find_data(t_region_d *data, void *ptr)
{
	if (data != NULL)
	{
		while (data != NULL && data->data != ptr)
			data = data->next;
	}
	return (data);
}
