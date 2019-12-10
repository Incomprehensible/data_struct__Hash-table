/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_hashtable.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 00:53:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/12/10 09:54:46 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_HASHTABLE_H
# define SH_HASHTABLE_H

# include "sh_req.h"

# define NOKEYMSG "No key specified\n"
# define NODATAFOUND "No data found for this key\n"
# define INSRTSUCCESS "Data was loaded\n"
# define MAXHASH (unsigned int)0xffffff
# define HASHBLOCKSIZE (unsigned int)0x40

int g_hashkill;
unsigned int (*g_hashfunc)(char *, unsigned int);

typedef struct		s_htx
{
	char			*key;
	char			*data;
	struct s_htx	*next;
}					t_htx;

t_htx				**access_hashtb(t_htx **new_tb, unsigned int sz);
void				insert_hashdata(char *key, char *data, t_htx **hashtable);
t_htx				**init_hashtb(t_htx **hashtable);
unsigned int		djb2_hash_func(char *key, unsigned int sz);
unsigned int		warzone_hash(char *key, unsigned int sz);
void				process_collision(char *key, char *data, t_htx *hashtable);
void				replace_hashdata(char *data, t_htx **node);
int					remove_hashdata(char *key, t_htx **hashtable);
t_htx				**resize_hashtb(unsigned int new_size);
t_htx				**resize_hashtble(t_htx **hashtable, unsigned int new_size);
t_htx				*make_new_hash(char *key, char *data);
void				into_new_hash(unsigned long int sz, t_htx *hashtable, \
t_htx **new_tb);
void				*delete_hashtble(t_htx **hashtable);
char				*fetch_hashdata(char *key, t_htx **hashtable);
t_htx				*search_hashkey(char *key, t_htx *node);
unsigned int		hashed_elems(t_htx **hashtable);
unsigned int		get_hashtb_size(void);
char				*display_hashtable(t_htx **hashtable);

#endif
