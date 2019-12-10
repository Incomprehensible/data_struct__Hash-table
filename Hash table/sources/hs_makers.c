/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_makers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 09:56:07 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_hashtable.h"

extern unsigned int g_size;

t_htx	**init_hashtb(t_htx **hashtable)
{
	g_hashfunc = g_hashfunc ? g_hashfunc : &djb2_hash_func;
	hashtable = (t_htx **)ft_memalloc(sizeof(t_htx *) * (g_size + 1));
	return (hashtable);
}

t_htx	*make_new_hash(char *key, char *data)
{
	t_htx	*hashtable;

	hashtable = (t_htx *)ft_memalloc(sizeof(t_htx));
	hashtable->key = ft_strdup(key);
	hashtable->data = ft_strdup(data);
	hashtable->next = NULL;
	return (hashtable);
}

t_htx	*teleport_data(t_htx *new_tb, t_htx *hashtable)
{
	new_tb = (t_htx *)ft_memalloc(sizeof(t_htx));
	while (hashtable)
	{
		new_tb = make_new_hash(hashtable->key, hashtable->key);
		hashtable = hashtable->next;
		while (hashtable)
		{
			process_collision(hashtable->key, hashtable->data, new_tb);
			hashtable = hashtable->next;
		}
	}
	return (new_tb);
}

t_htx	**split_rotate(t_htx **hashtable)
{
	t_htx				**new_tb;
	unsigned int		i;

	i = 0;
	new_tb = (t_htx **)ft_memalloc(sizeof(t_htx *) * (g_size + 1));
	i = g_size / 2;
	while (i <= g_size)
	{
		if (hashtable[i])
			new_tb[i] = teleport_data(new_tb[i], hashtable[i]);
		++i;
	}
	delete_hashtble(hashtable);
	return (new_tb);
}

t_htx	**resize_hashtble(t_htx **hashtable, unsigned int new_size)
{
	t_htx				**new_tb;
	unsigned int		i;

	i = 0;
	if (new_size >= MAXHASH || new_size + 1 < new_size)
		return (split_rotate(hashtable));
	new_tb = (t_htx **)ft_memalloc(sizeof(t_htx *) * (new_size + 1));
	while (i <= g_size)
	{
		if (hashtable[i])
			into_new_hash(new_size, hashtable[i], new_tb);
		++i;
	}
	return (new_tb);
}
