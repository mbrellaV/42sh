#include "fshell.h"

void        del_hist()
{
    ft_distruct_memory(globals()->g_memory_head);
    globals()->g_memory_head = make_memmory_with_one_node(-1, NULL);
}