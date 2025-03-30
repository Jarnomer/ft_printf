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

static void	justify_right(t_print *output)
{
	if (output->pad_char == '0' && output->prefix_len)
	{
		if (!print_char(output, output->sign_char))
			return ;
		output->prefix_len = 0;
	}
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
	if (output->prefix_len && !print_char(output, output->sign_char))
		return ;
	if (!print_chars(output, '0', output->zero_pad))
		return ;
	if (!print_nbr(output))
		return ;
}

static void	justify_left(t_print *output)
{
	if (output->prefix_len && !print_char(output, output->sign_char))
		return ;
	if (!print_chars(output, '0', output->zero_pad))
		return ;
	if (!print_nbr(output))
		return ;
	if (!print_chars(output, ' ', output->pad_len))
		return ;
}

static void	setup_string(t_print *output, long val)
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
			val /= 10;
			output->digit_count++;
		}
	}
}

static void	parse_prefix(t_print *output, long val)
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
	setup_string(output, ft_labs(val));
	calculate_pad(output);
	if (output->f_left)
		justify_left(output);
	else
		justify_right(output);
}
