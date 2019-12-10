/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_user_interface.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 09:50:27 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hs_interface.h"

t_htx		**get_hashtb(unsigned int sz, unsigned int f(char *, unsigned int))
{
	t_htx	**hashtable;

	g_hashfunc = f;
	g_hashkill = 0;
	hashtable = access_hashtb(NULL, sz);
	return (hashtable);
}

void		delete_hashtb(void)
{
	g_hashkill |= 1;
	access_hashtb(NULL, 0);
	g_hashkill ^= g_hashkill;
}

void		add_to_hashtb(char *key, char *data)
{
	t_htx	**hashtable;

	if (!key || !data)
		return ;
	if (!(hashtable = access_hashtb(NULL, 0)))
		return ;
	insert_hashdata(key, data, hashtable);
}

void		remove_hash(char *key)
{
	t_htx	**hashtable;

	if (!key)
		return ;
	if (!(hashtable = access_hashtb(NULL, 0)))
		return ;
	remove_hashdata(key, hashtable);
}

t_htx		**resize_hashtb(unsigned int new_size)
{
	t_htx	**new_tb;
	t_htx	**hashtable;

	if (!(hashtable = access_hashtb(NULL, 0)))
		return (NULL);
	if (hashed_elems(hashtable) > new_size)
		return (hashtable);
	new_tb = resize_hashtble(hashtable, new_size);
	access_hashtb(new_tb, new_size);
	return (new_tb);
}
