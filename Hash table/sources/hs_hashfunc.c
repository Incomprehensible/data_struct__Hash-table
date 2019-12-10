/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_hashfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 10:01:16 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_hashtable.h"

unsigned int	warzone_hash(char *key, unsigned int sz)
{
	unsigned long int	hash;
	unsigned int		ch;
	size_t				i;

	hash = 0;
	i = 0;
	while ((ch = key[i++]))
		hash += ch * i;
	hash ^= 0xfeadfeaddeadbeef;
	return (hash % sz);
}

unsigned int	djb2_hash_func(char *key, unsigned int sz)
{
	unsigned long int	hash;
	unsigned int		ch;

	hash = 5381;
	while ((ch = *key++))
		hash += (((hash << 5) + hash) + ch);
	return (hash % sz);
}
