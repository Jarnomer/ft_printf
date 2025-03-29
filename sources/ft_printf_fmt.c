/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:53:31 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:24:42 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	format_chr(t_print *output, int chr)
{
	if (output->width > 1)
	{
		output->pad_len = output->width - 1;
		if (output->f_minus)
		{
			if (ft_putchar_fd(chr, 1) == -1)
				output->length = -1;
			else
				output->length += 1;
			while (output->pad_len-- > 0 && output->result != -1)
				format_chr(output, ' ');
			return;
		}
		else
		{
			if (output->f_zero)
				output->pad_char = '0';
			while (output->pad_len-- > 0 && output->result != -1)
				format_chr(output, output->pad_char);
		}
	}
	if (ft_putchar_fd(chr, 1) == -1)
		output->length = -1;
	else
		output->length += 1;
}

void	format_str(t_print *output, char *str)
{
	if (!str)
		str = "(null)";
	output->temp = handle_precision(output, str, 0, 's');
	if (!output->temp)
	{
		output->length = -1;
		return;
	}
	output->calc_len = ft_strlen(output->temp);
	if (output->width > output->calc_len)
		apply_width(output, output->temp);
	else
	{
		output->result = ft_putstr_fd(output->temp, 1);
		if (output->result == -1)
			output->length = -1;
		else
			output->length += output->result;
	}
}

void	format_hex(t_print *output, unsigned long hex, char spec)
{
	if (spec == 'p' && hex == 0)
	{
		format_str(output, "(nil)");
		return;
	}
	if (spec == 'p' || ((spec == 'x' || spec == 'X')
		&& output->f_hash && hex != 0))
	{
		if (spec == 'X')
			format_str(output, "0X");
		else
			format_str(output, "0x");
	}
	if (hex >= 16)
		format_hex(output, hex / 16, spec);
	if (output->length == -1)
		return;
	if (spec == 'x' || spec == 'p')
		format_chr(output, HEXLOW[hex % 16]);
	else
		format_chr(output, HEXUPP[hex % 16]);
}











static void	format_int_width(t_print *output, long val, char *str)
{
	if (output->f_zero && !output->has_prec && !output->f_minus)
	{
		apply_prefix(output, val, 'd');
		apply_width(output, str);
	}
	else if (output->f_minus)
	{
		apply_prefix(output, val, 'd');
		apply_width(output, str);
	}
	else
	{
		output->calc_len = ft_strlen(str) + output->sign_offset;
		apply_width(output, str);
		if (output->length != -1)
			apply_prefix(output, val, 'd');
		output->result = ft_putstr_fd(str, 1);
		if (output->result == -1)
			output->length = -1;
		else
			output->length += output->result;
	}
}

static void	print_int_with_prefix(t_print *output, long val, char *str)
{
	apply_prefix(output, val, 'd');
	output->result = ft_putstr_fd(str, 1);
	if (output->result == -1)
		output->length = -1;
	else
		output->length += output->result;
}

void	format_int(t_print *output, long val)
{
	if (val < 0)
		output->is_negative = 1;
	if (val < 0 || output->f_plus || output->f_space)
		output->sign_offset = 1;
	output->abs_val = (val < 0) ? -val : val;
	output->temp = ft_itoa(output->abs_val);
	output->temp = handle_precision(output, output->temp, val, 'd');
	if (!output->temp)
	{
		output->length = -1;
		return;
	}
	output->calc_len = ft_strlen(output->temp) + output->sign_offset;
	if (output->width <= output->calc_len)
		print_int_with_prefix(output, val, output->temp);
	else
		format_int_width(output, val, output->temp);
}
