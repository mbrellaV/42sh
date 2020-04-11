#include "fshell.h"

t_exectoken		*all_parse(char *cmd)
{
	t_lextoken	*tmp;
	t_exectoken	*extmp;
	t_dop_str	*t;
	//t_lextoken	*dop_tmp;

	t = NULL;
	if (*cmd == '\0')
		return (NULL);
	ft_change_all_sc(cmd);
	//dprintf(2, "\ncmd|%s|\n", cmd);
	if (!(tmp = do_lexer(cmd)))
		return (NULL);
	//ft_strdel(&str_for_del);
//	dprintf(2, "\n10|%s|\n", cmd);
//	dop_tmp = tmp;
//	while (dop_tmp)
//	{
//		dprintf(2, "\n|%d, %s|\n", dop_tmp->is_near_opt, dop_tmp->line);
//		dop_tmp = dop_tmp->next;
//	}
	tmp = do_zam_bax_and_hist_full(tmp);
	if (tmp == NULL)
		return (NULL);
	if (check_all_errors(tmp) != 1)
	{
		ft_error(5, "\\n");
		ft_distr_lex(tmp);
		return (NULL);
	}
//	dop_tmp = tmp;
//	while (dop_tmp)
//	{
//		dprintf(2, "\n|%d, %s|\n", dop_tmp->is_near_opt, dop_tmp->line);
//		dop_tmp = dop_tmp->next;
//	}
	//exit(0);
	free(t);
	extmp = do_parser(tmp);
	do_zamena_opt_tokens(extmp);
	do_obr_zamena_slash(extmp);
//	t_exectoken *exdop = extmp;
//	while (exdop)
//	{
//		dprintf(2, "\n//");
//		ft_show_env(exdop->file_args);
//		dprintf(2, "\n//");
//		ft_show_env(exdop->file_opt);
//		dprintf(2, "\n//");
//		exdop = exdop->right;
//	}
	//exit(0);
	ft_distr_lex(tmp);
	return (extmp);
}