cmake_minimum_required(VERSION 3.14)
project(42save C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)
include_directories(libft/inc)
include_directories(src)
include_directories(src/qft_printf)

add_executable(42save
        src/builtins/ft_fc_3.c
        inc/fshell.h
        inc/hash.h
        inc/nucleus.h
        inc/parser.h
        inc/struct.h
        src/builtins/authors.c
        src/builtins/alias/alias.c
        src/builtins/allenv/ft_env.c
        src/builtins/allenv/global_env.c
        src/builtins/allenv/main_env.c
        src/builtins/bg_builtin.c
        src/builtins/fg_builtin.c
        src/builtins/ft_cd.c
        src/builtins/ft_cd_2.c
        src/builtins/ft_cd_3.c
        src/builtins/ft_echo.c
        src/builtins/ft_echo2.c
        src/builtins/ft_type.c
        src/errors/errror_handler.c
        src/exec/continuing_jobs.c
        src/exec/ft_create_file.c
        src/exec/ft_do_redirects.c
        src/exec/launch_job.c
        src/exec/launch_process.c
        src/exec/operating_job.c
        src/exec/put_job_in_background.c
        src/exec/put_job_in_foreground.c
        src/exec/stopped_and_terminated_jobs.c
        src/hash/hash_error.c
        src/hash/hash_table.c
        src/hash/hash_table_2.c
        src/lexer/all_bax_and_hist_change.c
        src/lexer/change_dol.c
        src/history/change_hist_exp.c
        src/lexer/change_sc.c
        src/lexer/change_spaces.c
        src/lexer/change_str_by_str.c
        src/lexer/check_errors.c
        src/lexer/cr_and_add_tokens.c
        src/lexer/create_new_lexer_struct.c
        src/lexer/dop_funs.c
        src/lexer/get_opt_type.c
        src/history/history_search.c
        src/lexer/kill_dop_structure.c
        src/lexer/lexer.c
        src/lexer/word_sizes.c
        src/lexer/zam_opt_in_tokens.c
        src/nucleus/del_readline.c
        src/nucleus/do_add.c
        src/nucleus/dop_tab_funs.c
        src/history/find_history.c
        src/nucleus/ft_add_intput_que.c
        src/nucleus/ft_add_sumchar.c
        src/nucleus/ft_arrdel.c
        src/nucleus/ft_arrnew.c
        src/nucleus/ft_arrows.c
        src/nucleus/ft_back_slovo.c
        src/nucleus/ft_c.c
        src/nucleus/ft_cheak_quote.c
        src/nucleus/ft_cleanstr.c
        src/nucleus/ft_cut.c
        src/nucleus/ft_cut_copy.c
        src/nucleus/ft_do_copy.c
        src/nucleus/ft_do_delch.c
        src/nucleus/ft_do_leftright.c
        src/nucleus/ft_downcursor.c
        src/history/init_history.c
        src/history/ft_add_to_history.c
        src/nucleus/ft_next_slovo.c
        src/nucleus/ft_print_tab.c
        src/nucleus/ft_directory.c
        src/nucleus/ft_read_8.c
        src/nucleus/ft_printf_helper.c
        src/nucleus/ft_put_n.c
        src/nucleus/ft_putcut.c
        src/history/dop_memory.c
        src/history/ft_putmemory.c
        src/nucleus/ft_read_8.c
        src/nucleus/ft_realloc_buff.c
        src/nucleus/ft_realloc_tab.c
        src/nucleus/ft_setcursor.c
        src/nucleus/ft_start_read.c
        src/nucleus/ft_strsplit1.c
        src/nucleus/ft_upcursor.c
        src/nucleus/ft_cheak_tab.c
        src/nucleus/input_mode.c
        src/history/show_history.c
        src/nucleus/tab.c
        src/parser/all_parse.c
        src/parser/change_tilda.c
        src/parser/check_bracket.c
        src/parser/dop_parser.c
        src/parser/main_parser.c
        src/check_file.c
        src/ft_distruct.c
        src/ft_error_q.c
        src/ft_signal.c
        src/ft_take_arg.c
        src/utility_files/g_builtins.c
        src/init_shell.c
        src/main.c
        src/builtins/alias/ft_do_change_alias.c
        src/builtins/alias/alias_error.c
        src/do_builtin.c
        src/ft_open_flag_in_builtins.c
        src/redirects.c
        src/utility_files/ft_get_prev_word.c
        src/shell_lvl.c src/exec/create_jobs_and_proc.c src/exec/free_job_list.c
        src/exec/find_jobs.c src/exec/working_with_fds.c src/exec/job_info.c
        src/exec/ft_do_open_flags.c src/exec/redirect.c src/ck_check.c
        src/lexer/del_one_node_in_lextokens.c src/ft_main_what.c src/put_error_to_env.c
        src/hash/print_hash.c src/parser/is_system_symbol.c
        src/builtins/ft_fc.c src/builtins/ft_fc_2.c src/utility_files/crc32.c src/lexer/do_zam_ravno.c
        src/nucleus/ft_cheak_tab.c src/nucleus/ft_directory.c src/nucleus/ft_find_env.c src/builtins/authors.c
        src/history/dop_memory.c src/redirects.c src/ft_open_flag_in_builtins.c src/do_builtin.c
        libft/src/count_words.c inc/history.h libft/src/ft_strcat_char.c src/history/save_hist.c inc/lexer.h
        inc/exec.h src/exec/ft_redirect_error.c src/lexer/do_zamena_slash.c src/builtins/exit_builtin.c
        src/utility_files/ft_get_prev_word.c src/builtins/kill_builtin.c src/builtins/allenv/ft_del_env_table.c
        src/evaln/calc_def_token.c
        src/evaln/atoimy.c
        src/evaln/calc.c
        src/evaln/dop.c
        src/evaln/calc_ltoa.c
        src/evaln/calc_atoi.c
        src/evaln/eval_expr.h
        src/evaln/ft_do_zam_eval.c
        src/evaln/inftopost.c src/evaln/ft_eval_parser.c src/evaln/opr_znak.c src/evaln/calc_lexer.c src/evaln/dop_word_funs.c)


target_link_libraries(42save ${CMAKE_SOURCE_DIR}/libft/libft.a)
target_link_libraries(42save termcap)
