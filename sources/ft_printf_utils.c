/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

bool	print_char(t_print *output, char c)
{
	if (ft_putchar_fd(c, 1) == -1)
	{
		output->error = true;
		output->length = -1;
		return (false);
	}
	output->length += 1;
	return (true);
}

bool	print_chars(t_print *output, char c, int count)
{
	while (count-- > 0)
	{
		if (!print_char(output, c))
			return (false);
	}
	return (true);
}

bool	print_str(t_print *output, const char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!print_char(output, str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	print_nbr(t_print *output)
{
	int	i;

	i = output->digit_count;
	while (--i >= 0)
	{
		if (!print_char(output, output->digits[i]))
			return (false);
	}
	return (true);
}
