/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/06 12:48:35 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_hashtable.h"

extern unsigned int size;

void    *delete_hashtble(t_htx **hashtable)
{
	unsigned long int   i;
	t_htx               *current;

	i = 0;
	while (i < size)
	{
		if (hashtable[i])
		{
			current = hashtable[i];
			while (current)
			{
				hashtable[i] = hashtable[i]->next;
				if (current->key)
					free(current->key);
				if (current->data)
					free(current->data);
				free(current);
				current = hashtable[i];
			}
		}
		++i;
	}
	free(hashtable);
	return (NULL);
}

void    process_collision(char *key, char *data, t_htx *hashtable)
{
	while (hashtable && hashtable->next)
		hashtable = hashtable->next;
	hashtable->next = make_new_hash(key, data);
}

void    replace_hashdata(char *data, t_htx **node)
{
	if ((*node)->data)
		free((*node)->data);
	(*node)->data = ft_strdup(data);
}

void    into_new_hash(unsigned long int sz, t_htx *hashtable, t_htx **new_tb)
{
	unsigned long int   hash;

	while (hashtable)
	{
		hash = hashfunc(hashtable->key, sz);
		new_tb[hash] = make_new_hash(hashtable->key, hashtable->key);
		hashtable = hashtable->next;
		while (hashtable)
		{
			process_collision(hashtable->key, hashtable->data, new_tb[hash]);
			hashtable = hashtable->next;
		}
	}
}

char    *fetch_hashdata(char *key, t_htx **hashtable)
{
	unsigned long int   hash;
	t_htx               *current;

	hash = hashfunc(key, size);
	current = hashtable[hash];
	while (current && ft_strcmp(current->key, key))
		current = current->next;
	return (current ? current->data : NULL);
}