/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	format_chr(t_print *output, int chr)
{
	if (output->width > 1)
	{
		output->pad_len = output->width - 1;
		if (output->f_zero && !output->f_minus)
			output->pad_char = '0';
	}
	if (output->f_minus)
	{
		if (!print_char(output, chr))
			return ;
		if (!print_chars(output, ' ', output->pad_len))
			return ;
	}
	else
	{
		if (!print_chars(output, output->pad_char, output->pad_len))
			return ;
		if (!print_char(output, chr))
			return ;
	}
}

void	format_str(t_print *output, char *str)
{
	if (!str)
		str = "(null)";
	output->str_len = ft_strlen(str);
	if (output->has_prec)
	{
		if (output->precision == 0)
			output->str_len = 0;
		else if (output->precision < output->str_len)
			output->str_len = output->precision;
	}
	if (output->width > output->str_len)
		output->pad_len = output->width - output->str_len;
	if (output->f_minus)
	{
		if (!print_str(output, str, output->str_len))
			return ;
		if (!print_chars(output, ' ', output->pad_len))
			return ;
	}
	else
	{
		if (!print_chars(output, ' ', output->pad_len))
			return ;
		if (!print_str(output, str, output->str_len))
			return ;
	}
}
