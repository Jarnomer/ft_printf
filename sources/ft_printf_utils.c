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

void	setup_pad(t_print *output)
{
	int	zero_padding;
	int	total_length;

	zero_padding = 0;
	if (output->has_prec && output->precision > output->digit_count)
		zero_padding = output->precision - output->digit_count;
	total_length = zero_padding + output->digit_count + output->prefix_len;
	if (output->width > total_length)
		output->pad_len = output->width - total_length;
	if (output->f_zero && !output->has_prec && !output->f_left)
		output->pad_char = '0';
	output->zero_pad = zero_padding;
	output->total_len = total_length;
}
