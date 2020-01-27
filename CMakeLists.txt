cmake_minimum_required(VERSION 3.14)
project(21end C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(21end
        inc/fshell.h
        inc/nucleus.h
        inc/parser.h
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
        src/lexer/do_subshell.c
        src/lexer/get_opt_type.c
        src/lexer/lexer.c
        src/nucleus/ft_cutcopy.c
        src/nucleus/ft_read_8.c
        src/nucleus/nucleus.c
        src/nucleus/nucleus2.c
        src/nucleus/nucleus3.c
        src/nucleus/nucleus4.c
        src/parser/dop_parser.c
        src/parser/change_tilda.c
        src/parser/main_parser.c
        src/ft_distruct.c
        src/ft_error_q.c
        src/ft_signal.c
        src/ft_take_arg.c
        src/main.c src/builtins/allenv/main_env.c src/builtins/alias/ft_alias.c src/evaln/ft_do_zam_eval.c
        src/evaln/atoimy.c src/evaln/inftopost.c src/evaln/calc.c src/evaln/dop.c)

target_link_libraries(21end ${CMAKE_SOURCE_DIR}/libft/libft.a)
target_link_libraries(21end termcap)