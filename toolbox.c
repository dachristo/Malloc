/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 22:24:13 by dchristo          #+#    #+#             */
/*   Updated: 2017/03/15 22:36:06 by dchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_alloc	*singleton(void)
{
	static t_alloc	*alloc = (t_alloc *)malloc(sizeof(t_alloc));
	return (t_alloc);
}

t_alloc *new_tiny(t_alloc *alloc)
{
	alloc->next_tiny = (t_alloc *)malloc(sizeof(t_alloc));
	return (alloc->next_tiny);
}

t_alloc *new_small(t_alloc *alloc)
{
	alloc->next_small = (t_alloc *)malloc(sizeof(t_alloc));
	return (alloc->next_small);
}
