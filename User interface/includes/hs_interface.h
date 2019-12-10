/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_interface.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 09:41:37 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HS_INTERFACE_H
# define HS_INTERFACE_H

# include "sh_hashtable.h"

t_htx			**get_hashtb(unsigned int sz, unsigned int \
f(char *, unsigned int));
void			delete_hashtb(void);
void			add_to_hashtb(char *key, char *data);
char			*pull_hash_data(char *key);
void			remove_hash(char *key);
t_htx			**resize_hashtb(unsigned int new_size);
unsigned int	count_hash(void);
unsigned int	count_free_hash(void);
unsigned int	hashtb_size(void);
void			display_hashtb(void);

#endif
