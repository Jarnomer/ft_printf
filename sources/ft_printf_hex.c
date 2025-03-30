/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	calculate_pad(t_print *output)
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

static void	justify_left(t_print *output)
{
	if (output->prefix_len > 0)
		if (!print_str(output, output->hex_prefix, output->prefix_len))
			return ;
	if (!print_chars(output, '0', output->zero_pad))
		return ;
	if (!print_nbr(output))
		return ;
	if (!print_chars(output, ' ', output->pad_len))
		return ;
}

static void	justify_right(t_print *output)
{
	if (output->pad_char == '0' && output->prefix_len > 0)
	{
		if (!print_str(output, output->hex_prefix, output->prefix_len))
			return ;
		output->prefix_len = 0;
	}
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
	if (output->prefix_len > 0)
		if (!print_str(output, output->hex_prefix, output->prefix_len))
			return ;
	if (!print_chars(output, '0', output->zero_pad))
		return ;
	if (!print_nbr(output))
		return ;
}

static void	setup_string(t_print *output, unsigned long val, char *hex_set)
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
			number = hex_set[val % 16];
			output->digits[output->digit_count] = number;
			val /= 16;
			output->digit_count++;
		}
	}
}

static void	parse_prefix(t_print *output, unsigned long val, char spec)
{
	if (spec == 'p')
	{
		output->hex_prefix[0] = '0';
		output->hex_prefix[1] = 'x';
		output->prefix_len = 2;
	}
	else if (output->f_hash && val != 0)
	{
		output->hex_prefix[0] = '0';
		output->hex_prefix[1] = spec;
		output->prefix_len = 2;
	}
}

void	format_hex(t_print *output, unsigned long val, char spec)
{
	if (spec == 'p' && val == 0)
	{
		format_str(output, "(nil)");
		return ;
	}
	parse_prefix(output, val, spec);
    if (!(val == 0 && output->has_prec && output->precision == 0))
	{
		if (spec == 'X')
			setup_string(output, val, HEXUPP);
		else
			setup_string(output, val, HEXLOW);
	}
	calculate_pad(output);
	if (output->f_left)
		justify_left(output);
	else
		justify_right(output);
}
