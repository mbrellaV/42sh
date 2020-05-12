/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:16:14 by wstygg            #+#    #+#             */
/*   Updated: 2020/05/12 17:28:00 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include <unistd.h>
# include <stdlib.h>

# define MAX_HASH	255

# define HASH_USAGE "hash [-r] [utility...]"

typedef struct		s_hash
{
	char			*key;
	char			*value;
	struct s_hash	*next;
}					t_hash;

int					do_hash(char **argv);
char				*hash_get(char *key, int no_error);
void				hash_init(void);
void				hash_clear(void);
int					print_hash();

char				*slash_cat(char *s1, char *s2);
void				hash_free_by_key(char *key);
void				free_hash(t_hash **hash);
t_hash				*hash_create(char *key, char *value);
unsigned char		str_to_hash(char *str);
char				*hash_error(int err, char *key, int no_error);

#endif
