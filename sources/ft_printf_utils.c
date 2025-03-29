/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/29 12:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	parse_width_prec(t_print *output, const char **format)
{
	if (ft_isdigit(**format))
	{
		output->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	if (**format == '.')
	{
		output->has_prec = 1;
		(*format)++;
		if (ft_isdigit(**format))
		{
			output->precision = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
	}
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
	else if ((spec == 'x' || spec == 'X') 
		&& output->f_hash && val != 0)
	{
		format_chr(output, '0');
		if (output->result != -1)
			format_chr(output, spec);
	}
}

void	apply_width(t_print *output, char *str)
{
	if (!str || output->width <= output->calc_len)
		return;
	if (output->f_zero && !output->has_prec)
		output->pad_char = '0';
	output->pad_len = output->width - output->calc_len;
	if (output->f_minus)
	{
		output->result = ft_putstr_fd(str, 1);
		while (output->pad_len-- > 0 && output->result != -1)
			format_chr(output, output->pad_char);
	}
	else
	{
		while (output->pad_len-- > 0 && output->result != -1)
			format_chr(output, output->pad_char);
		output->result = ft_putstr_fd(str, 1);
	}
	if (output->result == -1)
		output->length = -1;
	else
		output->length += output->result;
}
