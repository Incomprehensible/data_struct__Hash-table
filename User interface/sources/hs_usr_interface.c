/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_usr_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 09:36:41 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hs_interface.h"

unsigned int	count_hash(void)
{
	t_htx	**hashtable;

	if (!(hashtable = access_hashtb(NULL, 0)))
		return (0);
	return (hashed_elems(hashtable));
}

unsigned int	count_free_hash(void)
{
	t_htx	**hashtable;

	if (!(hashtable = access_hashtb(NULL, 0)))
		return (0);
	return (get_hashtb_size() - hashed_elems(hashtable));
}

unsigned int	hashtb_size(void)
{
	return (get_hashtb_size());
}

void			display_hashtb(void)
{
	t_htx	**hashtable;

	if (!(hashtable = access_hashtb(NULL, 0)))
		return ;
	display_hashtable(hashtable);
}

char			*pull_hash_data(char *key)
{
	t_htx	**hashtable;
	char	*data;

	if (!(hashtable = access_hashtb(NULL, 0)))
		return (NULL);
	if (!(data = fetch_hashdata(key, hashtable)))
		return (NODATAFOUND);
	return (data);
}
