/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmt2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/29 12:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	format_int_width(t_print *output, long val, char *str, int len)
{
	int	sign_offset;
	
	sign_offset = (val < 0 || output->f_plus || output->f_space) ? 1 : 0;
	
	if (output->f_zero && !output->has_prec && !output->f_minus)
	{
		apply_prefix(output, val, 'd');
		apply_width(output, str, len - sign_offset);
	}
	else if (output->f_minus)
	{
		apply_prefix(output, val, 'd');
		apply_width(output, str, len - sign_offset);
	}
	else
	{
		apply_width(output, str, len);
		if (output->length != -1)
			apply_prefix(output, val, 'd');
		output->result = ft_putstr_fd(str, 1);
		if (output->result == -1)
			output->length = -1;
		else
			output->length += output->result;
	}
}

static void	handle_hex_special(t_print *output, unsigned long hex, char spec)
{
	if (spec == 'p' && hex == 0)
	{
		format_str(output, "(nil)");
		return ;
	}
	if ((output->f_hash && hex != 0 && (spec == 'x' || spec == 'X')) 
		|| spec == 'p')
	{
		format_chr(output, '0');
		format_chr(output, (spec == 'X') ? 'X' : 'x');
	}
}

static void	print_hex_digit(t_print *output, unsigned long hex, char spec)
{
	if (spec == 'x' || spec == 'p')
		format_chr(output, HEXLOW[hex % 16]);
	else
		format_chr(output, HEXUPP[hex % 16]);
}

void	format_hex(t_print *output, unsigned long hex, char spec)
{
	if (spec == 'p' && hex == 0)
	{
		format_str(output, "(nil)");
		return ;
	}
	
	handle_hex_special(output, hex, spec);
	
	if (hex >= 16)
		format_hex(output, hex / 16, spec);
	
	if (output->length == -1)
		return ;
	
	print_hex_digit(output, hex, spec);
}

void	format_spec(t_print *output, va_list args, char spec)
{
	if (spec == '%')
		format_chr(output, '%');
	else if (spec == 'c')
		format_chr(output, va_arg(args, int));
	else if (spec == 's')
		format_str(output, va_arg(args, char *));
	else if (spec == 'i' || spec == 'd')
		format_int(output, va_arg(args, int));
	else if (spec == 'u')
		format_int(output, va_arg(args, unsigned int));
	else if (spec == 'x' || spec == 'X')
		format_hex(output, va_arg(args, unsigned int), spec);
	else if (spec == 'p')
		format_hex(output, va_arg(args, unsigned long), spec);
}