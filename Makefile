NAME		=	42sh

CC			=	gcc
FLAGS		=	#-Wall -Wextra -Werror
D_FLAGS		=	-g

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)libft.h

LIBS		=	-ltermcap

SRC_DIR		=	src/
INC_DIR		=	inc/
OBJ_DIR		=	objs/

SRC_BASE = builtins/ft_cd.c\
	builtins/ft_cd_2.c\
	builtins/ft_cd_3.c\
	builtins/ft_echo.c\
	builtins/ft_echo2.c\
	builtins/ft_fc.c\
	builtins/ft_fc_2.c\
	builtins/ft_fc_3.c\
	builtins/authors.c\
	builtins/allenv/ft_env.c\
	builtins/alias/alias.c\
	builtins/alias/alias_error.c\
	builtins/alias/ft_do_change_alias.c\
 	builtins/allenv/global_env.c\
 	ft_main_what.c\
 	ft_malloc.c\
 	qft_printf/add_buff.c\
 	qft_printf/add_char.c\
 	qft_printf/add_d.c\
 	qft_printf/add_str.c\
 	qft_printf/ft_add_c_s_d.c\
 	qft_printf/ft_add_double.c\
 	qft_printf/ft_dtoa.c\
 	qft_printf/ft_itoa_base_c.c\
 	qft_printf/ft_math.c\
 	qft_printf/ft_okr_double.c\
 	qft_printf/ft_oxu.c\
 	qft_printf/ft_pars.c\
 	qft_printf/ft_pars2.c\
 	qft_printf/ft_pointer.c\
 	qft_printf/ft_pr_help.c\
 	qft_printf/ft_printf.c\
 	errors/errror_handler.c\
 	exec/ft_create_file.c\
 	exec/ft_do_redirects.c\
 	exec/ft_do_open_flags.c\
 	exec/redirect.c\
 	exec/stopped_and_terminated_jobs.c\
 	exec/continuing_jobs.c\
 	exec/operating_job.c\
 	exec/find_jobs.c\
 	exec/free_job_list.c\
	builtins/fg_builtin.c\
	builtins/bg_builtin.c\
 	exec/ft_fun_fork.c\
 	exec/launch_job.c\
 	exec/put_job_in_foreground.c\
 	exec/put_job_in_background.c\
 	exec/launch_process.c\
 	exec/job_info.c\
 	exec/working_with_fds.c\
 	exec/create_jobs_and_proc.c\
	lexer/lexer.c\
	lexer/change_dol.c\
	lexer/change_spaces.c\
	lexer/cr_and_add_tokens.c\
	lexer/dop_funs.c\
	lexer/all_bax_and_hist_change.c\
	lexer/kill_dop_structure.c\
	lexer/del_one_node_in_lextokens.c\
	lexer/do_zam_ravno.c\
	lexer/word_sizes.c\
	lexer/change_hist_exp.c\
	lexer/change_str_by_str.c\
	lexer/get_opt_type.c\
	lexer/history_search.c\
	lexer/change_sc.c\
	lexer/check_errors.c\
	lexer/create_new_lexer_struct.c\
	lexer/zam_opt_in_tokens.c\
	nucleus/ft_read_8.c\
	nucleus/ft_c.c\
	nucleus/input_mode.c\
	nucleus/do_add.c\
	nucleus/ft_realloc_buff.c\
	nucleus/ft_cleanstr.c\
	nucleus/ft_setcursor.c\
	nucleus/ft_add_sumchar.c\
	nucleus/ft_put_n.c\
	nucleus/ft_do_leftright.c\
	nucleus/ft_find_env.c\
	nucleus/ft_upcursor.c\
	nucleus/ft_downcursor.c\
	nucleus/ft_back_slovo.c\
	nucleus/ft_next_slovo.c\
	nucleus/ft_arrows.c\
	nucleus/ft_putcut.c\
	nucleus/ft_cut.c\
	nucleus/dop_memory.c\
	nucleus/dop_tab_funs.c\
	nucleus/ft_do_delch.c\
	nucleus/ft_cut_copy.c\
	nucleus/ft_do_copy.c\
	nucleus/ft_strsplit1.c\
	nucleus/ft_print_tab.c\
	nucleus/ft_realloc_tab.c\
	nucleus/show_history.c\
	nucleus/ft_head_memory.c\
	nucleus/ft_memory.c\
	nucleus/ft_dop_history.c\
	nucleus/ft_putmemory.c\
	nucleus/ft_directory.c\
	nucleus/ft_start_read.c\
	nucleus/ft_printf_helper.c\
	nucleus/ft_cheak_quote.c\
	nucleus/ft_cheak_tab.c\
	nucleus/ft_add_intput_que.c\
	nucleus/find_history.c\
	nucleus/ft_arrnew.c\
	nucleus/ft_arrdel.c\
	nucleus/del_readline.c\
	nucleus/tab.c\
	parser/dop_parser.c\
	parser/change_tilda.c\
	parser/main_parser.c\
	parser/check_bracket.c\
	parser/all_parse.c\
	parser/create_dop_struct.c\
	parser/is_system_symbol.c\
	hash/hash_table.c\
	hash/hash_table_2.c\
	hash/hash_error.c\
	hash/print_hash.c\
	evaln/dop.c\
	evaln/calc.c\
	evaln/atoimy.c\
	evaln/inftopost.c\
	evaln/ft_do_zam_eval.c\
	evaln/sub_and_add.c\
	evaln/calc_error.c\
    evaln/change_vars.c\
    evaln/check_calc.c\
    calc/calc_add_fun.c\
    calc/calc.c\
    calc/calc_lexer.c\
	calc/calc_arr_tkns.c\
	calc/calc_mul_fun.c\
	calc/calc_inc_fun.c\
	calc/calc_com_fun.c\
	calc/calc_eq_fun.c\
	calc/calc_log_fun.c\
	calc/calc_tkn.c\
	calc/calc_num_fun.c\
	calc/calc_parent_fun.c\
	calc/calc_error_fun.c\
	calc/calc_var_fun.c\
	calc/calc_var_tkn.c\
	calc/calc_arr_reloc.c\
	calc/calc_atoi.c\
	calc/calc_ltoa.c\
	calc/change_vars.c\
	calc/ft_do_zam_eval.c\
	utility_files/g_builtins.c\
	utility_files/global.c\
	utility_files/crc32.c\
	put_error_to_env.c\
	ft_distruct.c\
	ft_error_q.c\
	ft_signal.c\
	ft_take_arg.c\
	check_file.c\
	main.c\
	ck_check.c\
	shell_lvl.c\
	init_shell.c\
	builtins/allenv/main_env.c\
	builtins/ft_type.c\
	ft_whatis.c\
	redirects.c\
	do_builtin.c\
	ft_open_flag_in_builtins.c\



SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

$(NAME):		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) \
		$(LIBFT_LIB) \
		$(FLAGS) $(D_FLAGS)
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(NAME)\033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) $(FLAGS) $(D_FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(NAME).\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME).\033[0m\033[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib

-include $(OBJS:.o=.d)
