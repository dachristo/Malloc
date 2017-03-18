/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/18 16:31:44 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc	*singleton(void)
{
	t_alloc *alloc = (t_alloc *)mmap(0, sizeof(t_alloc), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	return (alloc);
}

t_region_d *new_tiny(t_region_d *data_tiny)
{
	data_tiny = (t_region_d *)mmap(0, sizeof(t_region_d) + TINY, PROT_READ |
			PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	data_tiny->next = NULL;
	data_tiny->prev = NULL;
	return (data_tiny);
}
