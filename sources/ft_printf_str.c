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

static void	justify_right(t_print *output, char *str)
{
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
	if (!print_str(output, str, output->str_len))
		return ;
}

static void	justify_left(t_print *output, char *str)
{
	if (!print_str(output, str, output->str_len))
		return ;
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
}

static void	parse_prefix(t_print *output, char **str)
{
	if (output->has_prec)
	{
		if (output->precision == 0)
			output->str_len = 0;
		else if (!output->precision || output->precision < output->str_len)
		{
			if (!ft_strcmp(*str, "(null)") && output->precision < 6)
				output->str_len = 0;
			else
				output->str_len = output->precision;
		}
	}
}

void	format_str(t_print *output, char *str)
{
	if (!str)
		str = "(null)";
	output->str_len = ft_strlen(str);
	parse_prefix(output, &str);
	if (output->width > output->str_len)
		output->pad_len = output->width - output->str_len;
	if (output->f_left)
		justify_left(output, str);
	else
		justify_right(output, str);
}
