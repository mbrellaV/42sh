#ifndef LEXER_H
#define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "struct.h"
# include "nucleus.h"
# include "../libft/inc/libft.h"
# include <unistd.h>

typedef struct				s_lextoken
{
	struct s_lextoken		*prev;
	struct s_lextoken		*next;
	int						is_near_opt;
	char					*line;
	int						operator_type;
	int						inhibitor_lvl;
	int						is_near_word;
}							t_lextoken;

typedef struct				s_exectoken
{
	int						wait_and;
	int						wait_or;
	struct s_exectoken		*left;
	struct s_exectoken		*right;
	char					**file_args;
	char					**file_opt;
	int						foreground;
}							t_exectoken;

typedef struct				s_dop_str
{
	int						f_a;
	int						dopi_a;
	t_lextoken				*dop_a;
	t_exectoken				*tmp1_a;
	char					*str_b;
	int						i_c;
	t_exectoken				*prevdot_c;
	t_exectoken				*prev_c;
	t_exectoken				*start_c;
	char					*tmp_c;
	int						dop_c;
	int						d_c;
	t_lextoken				*tail_c;
	t_lextoken				*doptail_c;
}							t_dop_str;

/*
** all_bax_and_hist_change.c
*/

t_lextoken		*do_zam_bax_and_hist_full(t_lextoken *h, t_lextoken **save_tmp);

/*
** change_dol.c
*/

char			*do_zam_str_bax(char *str1, t_dop_str *t);

/*
** change_sc.c
*/

void			ft_change_all_sc(char *str);

/*
** change_spaces.c
*/

int				do_zamena_slash(char *line, t_readline *p);
char			*do_reverse_zamena(char *str);
void			do_obr_zamena_slash(t_exectoken *tmp);
char			*do_obr_zamena(char *line);

/*
** change_str_by_str.c
*/

char			*do_zam_str_by_str(int start, int end, char *str, char *zam_str);

/*
** check_errors.c
*/

int				check_all_errors(t_lextoken *tmp);

/*
** cr_and_add_tokens.c
*/

t_lextoken		*add_token(t_lextoken *start, char *line);
t_lextoken		*ft_cr_new_token(char *line, int op_type);

/*
** create_new_lexer_struct.c
*/

t_dop_str		*cr_dop_str(char **line1);

/*
** del_one_node_in_lextokens.c
*/

void			del_one_node(t_lextoken *token_to_del, t_lextoken **first_token);


/*
** do_zam_ravno.c
*/

t_lextoken		*do_zam_ravno(t_lextoken *h, t_lextoken **first_token);

/*
** dop_funs.c
*/

int				ispar(char c);
int				issc(char c);
int				isoperator(char c);
char			find_pair_sc(char c);
int				isword(char c);

/*
** get_opt_type.c
*/

int				get_op_type(char *operator);
int				needs_something_before(int n);

/*
** kill_dop_structure.c
*/

t_lextoken		*ft_kill_str_dop_lex(t_dop_str *t, t_lextoken *tmp);
t_exectoken		*ft_kill_str_dop_exec(t_dop_str *t, t_exectoken *tmpexec);

/*
** lexer.c
*/

t_lextoken		*do_lexer(char *line);

/*
** word_sizes.c
*/

int				operator_size(char *str);
int				size_with_bax(char *str);
int				word_size(char *str);
int				c_size(char *str, char b);
int				sc_size(char *str, char b);

/*
** zam_opt_tokens.c
*/

void		do_zamena_opt_tokens(t_exectoken *tmp);

#endif //INC_42SAVE_LEXER_H
