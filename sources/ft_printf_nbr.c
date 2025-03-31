/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline void	justify_right(t_print *output)
{
	if (output->pad_char == '0' && output->prefix_len)
	{
		if (print_char(output, output->sign_char) == -1)
			return ;
		output->prefix_len = 0;
	}
	if (print_chars(output, output->pad_char, output->pad_len) == -1)
		return ;
	if (output->prefix_len)
		if (print_char(output, output->sign_char) == -1)
			return ;
	if (print_chars(output, '0', output->zero_pad) == -1)
		return ;
	print_nbr(output);
}

static inline void	justify_left(t_print *output)
{
	if (output->prefix_len)
		if (print_char(output, output->sign_char) == -1)
			return ;
	if (print_chars(output, '0', output->zero_pad) == -1)
		return ;
	if (print_nbr(output) == -1)
		return ;
	print_chars(output, ' ', output->pad_len);
}

static inline void	setup_string(t_print *output, long val)
{
	char	number;

	if (val == 0)
	{
		output->digits[output->digit_count] = '0';
		output->digit_count++;
	}
	else
	{
		while (val > 0)
		{
			number = val % 10 + '0';
			output->digits[output->digit_count] = number;
			output->digit_count++;
			val /= 10;
		}
	}
}

static inline void	parse_prefix(t_print *output, long val)
{
	if (val < 0)
	{
		output->sign_char = '-';
		output->prefix_len = 1;
	}
	else if (output->f_plus)
	{
		output->sign_char = '+';
		output->prefix_len = 1;
	}
	else if (output->f_space)
	{
		output->sign_char = ' ';
		output->prefix_len = 1;
	}
}

void	format_nbr(t_print *output, long val)
{
	parse_prefix(output, val);
	if (!(val == 0 && output->has_prec && output->precision == 0))
		setup_string(output, ft_labs(val));
	setup_hex_nbr_pad(output);
	if (output->f_left)
		justify_left(output);
	else
		justify_right(output);
}
