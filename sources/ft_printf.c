/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	reset_flags(t_print *output)
{
	int	len;

	len = output->length;
	ft_bzero(output, sizeof(t_print));
	output->length = len;
	output->pad_char = ' ';
}

static void	parse_flags(t_print *output, const char **format)
{
	while (**format && ft_strchr(FLAGS, **format))
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
	parse_width_prec(output, format);
	if (output->f_minus)
		output->f_zero = 0;
	if (output->f_plus)
		output->f_space = 0;
}

static void	parse_specs(t_print *output, va_list args, char spec)
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

int	ft_printf(const char *format, ...)
{
	t_print	output;
	va_list	args;

	output.length = 0;
	va_start(args, format);
	while (*format)
	{
		reset_flags(&output);
		if (*format != '%')
			format_chr(&output, *format);
		else if (*++format)
		{
			parse_flags(&output, &format);
			if (ft_strchr(SPECS, *format))
				parse_specs(&output, args, *format);
		}
		ft_free_single((void **)&output.temp);
		if (output.length == -1 || !*format)
			break ;
		format++;
	}
	va_end(args);
	return (output.length);
}
