/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 09:59:22 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_hashtable.h"
#include <stdio.h>

unsigned int g_size;

t_htx	**access_hashtb(t_htx **new_tb, unsigned int sz)
{
	static t_htx	**hashtable;

	if ((g_hashkill || new_tb))
	{
		if (!hashtable)
			return (NULL);
		hashtable = delete_hashtble(hashtable);
		if (new_tb && (g_size = sz))
			hashtable = new_tb;
		return (hashtable);
	}
	if (hashtable)
		return (hashtable);
	g_size = sz ? sz : HASHBLOCKSIZE;
	if (!hashtable)
		hashtable = init_hashtb(hashtable);
	return (hashtable);
}

char	*display_hashtable(t_htx **hashtable)
{
	unsigned int	i;
	t_htx			*current;

	i = 0;
	while (i < g_size)
	{
		current = hashtable[i];
		while (current)
		{
			printf("[ key: %s data: %s ]\n", current->key, current->data);
			current = current->next;
		}
		++i;
	}
	return (0);
}

t_htx	*del_hashdata(t_htx *hashtable, t_htx **delim)
{
	t_htx	*after;
	t_htx	*start;

	start = hashtable;
	if (hashtable == *delim)
	{
		after = (*delim)->next;
		start = after;
	}
	else
	{
		while (hashtable && hashtable->next != *delim)
			hashtable = hashtable->next;
		if (!hashtable)
			return (hashtable);
		after = (*delim)->next;
		hashtable->next = after;
	}
	if ((*delim)->key)
		free((*delim)->key);
	if ((*delim)->data)
		free((*delim)->data);
	free(*delim);
	return (start);
}

int		remove_hashdata(char *key, t_htx **hashtable)
{
	unsigned int	hash;
	t_htx			*node;

	hash = g_hashfunc(key, g_size);
	if (hashtable[hash])
	{
		if (!(node = search_hashkey(key, hashtable[hash])))
			return (0);
		else
			hashtable[hash] = del_hashdata(hashtable[hash], &node);
		return (1);
	}
	return (0);
}

void	insert_hashdata(char *key, char *data, t_htx **hashtable)
{
	unsigned int		hash;
	unsigned int		hashed;
	t_htx				*node;
	t_htx				**new_tb;

	hashed = hashed_elems(hashtable);
	hash = g_hashfunc(key, g_size);
	if (hashed && (float)hashed / (float)g_size >= 0.7)
	{
		new_tb = resize_hashtble(hashtable, g_size << 1);
		hashtable = access_hashtb(new_tb, g_size << 1);
	}
	if (hashtable[hash])
	{
		if (!(node = search_hashkey(key, hashtable[hash])))
			process_collision(key, data, hashtable[hash]);
		else
			replace_hashdata(data, &node);
		return ;
	}
	hashtable[hash] = make_new_hash(key, data);
}
