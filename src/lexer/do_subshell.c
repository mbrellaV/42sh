#include "../../inc/fshell.h"

int					dop_subshell(char *str, t_memory *head)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	if (!ft_strstr(str, "("))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			newstr = ft_strsub(str, i + 1, sc_size(str, '(') - i - 3);
			break ;
		}
		i++;
	}
//	ft_printf("fevsavafsv///////////////// %s ", newstr);
	if (newstr != NULL)
	{
		//	ft_printf("\n///////// %s\n", newstr);
		do_cmd(newstr, head);
		//	ft_printf("fevsavafsv/////////////////123");
		return (1);
	}
	else
		return (-1);
}

int					do_work_subshell(char **mas, t_memory *head)
{
	int		i;

//	ft_printf("sas");
	i = dop_subshell(mas[0], head);
///	ft_printf("\nfff: %d \n rofler: %s\n", i, mas[0]);
	if (i == 0)
		return (0);
	else if (i == -1)
		return (-1);
	if (mas[1] != NULL)
		return (-1);
	ft_printf("sas1");
	return (1);
}