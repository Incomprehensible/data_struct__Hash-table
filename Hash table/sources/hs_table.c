/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/06 22:53:06 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_hashtable.h"
#include <stdio.h>

unsigned int size;

t_htx               **access_hashtb(t_htx **new_tb, unsigned int sz)
{
	static t_htx        **hashtable;

	if ((hashkill || new_tb))
	{
		if (!hashtable)
			return (NULL);
		hashtable = delete_hashtble(hashtable);
		if (new_tb && (size = sz))
			hashtable = new_tb;
		return (hashtable);
	}
	if (hashtable)
		return (hashtable);
	size = sz ? sz : HASHBLOCKSIZE;
	if (!hashtable)
		hashtable = init_hashtb(hashtable);
	return (hashtable);
}

char                *display_hashtable(t_htx **hashtable)
{
	unsigned int    i;
	t_htx           *current;

	i = 0;
	while (i < size)
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

t_htx   *del_hashdata(t_htx *hashtable, t_htx **delim)
{
	t_htx               *after;
	t_htx               *start;

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

int                remove_hashdata(char *key, t_htx **hashtable)
{
	unsigned int    hash;
	t_htx           *node;

	hash = hashfunc(key, size);
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

void                insert_hashdata(char *key, char *data, t_htx **hashtable)
{
	unsigned int        hash;
	unsigned int        hashed;
	t_htx               *node;
	t_htx               **new_tb;

	hashed = hashed_elems(hashtable);
	hash = hashfunc(key, size);
	if (hashed && (float)hashed / (float)size >= 0.7)
	{
		new_tb = resize_hashtble(hashtable, size << 1);
		hashtable = access_hashtb(new_tb, size << 1);
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

// void                insert_hashdata(char *key, char *data, t_htx **hashtable)
// {
// 	unsigned long int   hash;
// 	unsigned int        hashed;
// 	t_htx               *node;
// 	t_htx               **old_tb;

// 	hashed = hashed_elems(hashtable);
// 	hash = hashfunc(key, size);
// 	if (hashed && hashed / size >= 0.7)
// 	{
// 		old_tb = hashtable;
// 		hashtable = resize_hashtble(hashtable, size << 1);
// 		delete_hashtble(old_tb);
// 		size <<= 1;
// 	}
// 	if (hashtable[hash])
// 	{
// 		if (!(node = search_hashkey(key, hashtable[hash])))
// 			process_collision(key, data, hashtable[hash]);
// 		else
// 			replace_hashdata(data, &node);
// 		return ;
// 	}
// 	hashtable[hash] = make_new_hash(key, data);
// }

// t_htx               **insert_hashdata(char *key, char *data, t_htx **hashtable)
// {
// 	unsigned long int   hash;
// 	t_htx               *node;

// 	if (hashed_elems(hashtable) / size >= 0.7)
// 		hashtable = resize_hashtb(hashtable);
// 	hash = djb2_hash_func(key, size);
// 	if (hashtable[hash])
// 	{
// 		if (!(node = search_hashkey(key, hashtable[hash])))
// 			process_collision(key, data, hashtable[hash]);
// 		else
// 			replace_hashdata(data, &node);
// 		return (hashtable);
// 	}
// 	hashtable[hash]  = make_new_hash(key, data);
// 	return (hashtable);
// }


// char    *access_hashtb(char *key, char *data)
// {
// 	static t_htx    **hashtable;

// 	if (!hashtable && (size = 11))
// 		hashtable = init_hashtb(hashtable, size);
// 	if (!key && !data)
// 		hashtable = delete_hashtb(hashtable);
// 	else if (!key)
// 		return (display_hashtable(hashtable));
// 	else if (key && data)
// 	{
// 		hashtable = insert_hashdata(key, data, hashtable);
// 		return (INSRTSUCCESS);
// 	}
// 	else if (!(data = fetch_hashdata(key, hashtable)))
// 		return (NODATAFOUND);
// 	return (data);
// }

// t_htx   *del_hashdata(t_htx *hashtable, t_htx *delim)
// {
// 	t_htx               *after;
// 	t_htx               *current;

// 	current = hashtable;
// 	while (hashtable && hashtable != delim)
// 	{
// 		current = hashtable;
// 		hashtable = hashtable->next;
// 	}
// 	if (!hashtable)
// 		return (hashtable);
// 	after = hashtable->next;
// 	if (current != hashtable)
// 		current->next = after;
// 	if (hashtable->key)
// 		free(hashtable->key);
// 	if (hashtable->data)
// 		free(hashtable->data);
// 	free(hashtable);
// 	return (current);
// }

// void                del_hashdata(t_htx *hashtable, t_htx *delim)
// {
// 	t_htx               *after;
// 	t_htx               *current;

// 	current = hashtable;
// 	while (current && current != delim && current->next != delim)
// 		current = current->next;
// 	if (!current)
// 		return ;
// 	after = current->next->next;
// 	if (current->next->key)
// 		free(current->next->key);
// 	if (current->next->data)
// 		free(current->next->data);
// 	free(current->next);
// 	current->next = after;
// }

//find path of binary function body here