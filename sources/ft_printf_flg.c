/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/29 12:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	reset_flags(t_print *output)
{
	output->result = 0;
	output->f_minus = 0;
	output->f_zero = 0;
	output->f_hash = 0;
	output->f_plus = 0;
	output->f_space = 0;
	output->width = 0;
	output->precision = 0;
	output->has_prec = 0;
}

void	parse_flag_chars(t_print *output, const char **format)
{
	while (**format && ft_strchr("-0# +", **format))
	{
		if (**format == '-')
			output->f_minus = 1;
		else if (**format == '0')
			output->f_zero = 1;
		else if (**format == '#')
			output->f_hash = 1;
		else if (**format == '+')
			output->f_plus = 1;
		else if (**format == ' ')
			output->f_space = 1;
		(*format)++;
	}
}

void	parse_width_prec(t_print *output, const char **format)
{
	if (**format >= '1' && **format <= '9')
	{
		output->width = ft_atoi(*format);
		while (**format >= '0' && **format <= '9')
			(*format)++;
	}
	if (**format == '.')
	{
		output->has_prec = 1;
		(*format)++;
		if (**format >= '0' && **format <= '9')
		{
			output->precision = ft_atoi(*format);
			while (**format >= '0' && **format <= '9')
				(*format)++;
		}
	}
}

void	parse_flags(t_print *output, const char **format)
{
	parse_flag_chars(output, format);
	parse_width_prec(output, format);
	
	// Resolve flag conflicts
	if (output->f_minus)
		output->f_zero = 0;
	if (output->f_plus)
		output->f_space = 0;
}

void	apply_prefix(t_print *output, long val, char spec)
{
	if (spec == 'd' || spec == 'i')
	{
		if (val < 0)
			format_chr(output, '-');
		else if (output->f_plus)
			format_chr(output, '+');
		else if (output->f_space)
			format_chr(output, ' ');
	}
	else if ((spec == 'x' || spec == 'X') && output->f_hash && val != 0)
	{
		format_chr(output, '0');
		format_chr(output, spec);
	}
}