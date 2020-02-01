cmake_minimum_required(VERSION 3.14)
project(21end C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(21end
        inc/fshell.h
        inc/parser.h
        inc/nucleus.h
        inc/struct.h
        inc/hash.h
        src/builtins/ft_cd.c
        src/builtins/ft_echo.c
        src/builtins/ft_echo2.c
        src/builtins/allenv/ft_env.c
        src/errors/errror_handler.c
        src/exec/ft_create_file.c
        src/exec/ft_do_pipe.c
        src/exec/ft_fun_fork.c
        src/lexer/lexer.c
        src/lexer/change_dol.c
        src/lexer/change_spaces.c
        src/lexer/cr_and_add_tokens.c
        src/lexer/dop_funs.c
        src/lexer/kill_dop_structure.c
        src/lexer/word_sizes.c
        src/lexer/change_hist_exp.c
        src/lexer/change_str_by_str.c
        src/lexer/get_opt_type.c
        src/lexer/lexer.c
        src/nucleus/ft_read_8.c
        src/nucleus/ft_c.c
        src/nucleus/input_mode.c
        src/nucleus/do_add.c
        src/nucleus/ft_realloc_buff.c
        src/nucleus/ft_cleanstr.c
        src/nucleus/ft_setcursor.c
        src/nucleus/ft_add_sumchar.c
        src/nucleus/ft_put_n.c
        src/nucleus/ft_do_leftright.c
        src/nucleus/ft_upcursor.c
        src/nucleus/ft_downcursor.c
        src/nucleus/ft_back_slovo.c
        src/nucleus/ft_next_slovo.c
        src/nucleus/ft_arrows.c
        src/nucleus/ft_putcut.c
        src/nucleus/ft_cut.c
        src/nucleus/ft_do_delch.c
        src/nucleus/ft_cut_copy.c
        src/nucleus/ft_do_copy.c
        src/nucleus/ft_strsplit1.c
        src/nucleus/ft_print_tab.c
        src/nucleus/ft_realloc_tab.c
        src/nucleus/show_history.c
        src/nucleus/ft_head_memory.c
        src/nucleus/ft_memory.c
        src/nucleus/ft_dop_history.c
        src/nucleus/ft_putmemory.c
        src/nucleus/ft_start_read.c
        src/nucleus/ft_printf_helper.c
        src/nucleus/ft_cheak_quote.c
        src/nucleus/ft_add_intput_que.c
        src/nucleus/ft_arrnew.c
        src/nucleus/ft_arrdel.c
        src/nucleus/del_readline.c
        src/nucleus/find_history.c
        src/nucleus/tab.c
        src/parser/dop_parser.c
        src/parser/change_tilda.c
        src/parser/main_parser.c
        src/hash/hash_table.c
        src/hash/hash_table_2.c
        src/hash/hash_error.c
        src/ft_distruct.c
        src/ft_error_q.c
        src/ft_signal.c
        src/ft_take_arg.c
        src/main.c src/builtins/allenv/main_env.c src/check_file.c src/lexer/history_search.c src/nucleus/dop_tab_funs.c src/builtins/allenv/global_env.c src/shell_lvl.c src/lexer/all_bax_and_hist_change.c)


target_link_libraries(21end ${CMAKE_SOURCE_DIR}/libft/libft.a)
target_link_libraries(21end termcap)