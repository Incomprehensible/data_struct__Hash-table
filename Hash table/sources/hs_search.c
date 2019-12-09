/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/06 12:23:34 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_hashtable.h"

extern unsigned int size;

t_htx   *search_hashkey(char *key, t_htx *node)
{
	while (node && ft_strcmp(node->key, key))
		node = node->next;
	return (node);
}

unsigned int   hashed_elems(t_htx **hashtable)
{
	unsigned long int   hashed;
	unsigned long int   i;
	t_htx               *current;

	i = 0;
	hashed = 0;
	while (i < size)
	{
		if (hashtable[i])
		{
			++hashed;
			current = hashtable[i]->next;
			while (current)
			{
				++hashed;
				current = current->next;
			}
		}
		i++;
	}
	return (hashed);
}

unsigned int    get_hashtb_size(void)
{
	return (size);
}