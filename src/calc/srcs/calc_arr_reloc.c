#include "fshell.h"

t_calc_tkns	*calc_reloc_tkns(t_calc_tkns *s_tokens)
{
	t_calc_tkn		*new_tokens;

	if (!s_tokens)
		return (NULL);
	if (!(new_tokens = (t_calc_tkn *)malloc(sizeof(t_calc_tkn)
		* (s_tokens->malloc_size + CALC_TOKENS_SIZE))))
		return (s_tokens);
	new_tokens = ft_memcpy(new_tokens, s_tokens->first_token, sizeof(t_calc_tkn)
															  * s_tokens->malloc_size);
	free(s_tokens->first_token);
	s_tokens->first_token = new_tokens;
	s_tokens->malloc_size += CALC_TOKENS_SIZE;
	return (s_tokens);
}