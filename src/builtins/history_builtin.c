#include "fshell.h"

int		hist_builtin(char **mas)
{
    if (mas[0] != NULL && mas[1] == NULL)
        show_history(globals()->g_memory_head);
    else if (mas[0] != NULL && mas[1] != NULL && mas[2] == NULL)
    {
        if (!ft_strcmp(mas[1], "clear"))
        {
            del_hist();
            return (0);
        }
    }
    return (0);
}