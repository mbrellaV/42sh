#include "calc.h"

static int	calc_is_whitespace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r'
		|| c == '\n' || c == ' ')
		return (1);
	return (0);
}

long long	calc_ll_atoi(const char *str)
{
	long long			sign;
	unsigned long long	res;

	if (!str)
		return (0);
	sign = 1;
	res = 0;
	while (calc_is_whitespace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (sign * res);
}
