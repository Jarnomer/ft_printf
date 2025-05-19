/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	print_char(t_print *output, char c)
{
	if (write(1, &c, 1) == -1)
	{
		output->length = -1;
		return (-1);
	}
	output->length += 1;
	return (0);
}

int	print_chars(t_print *output, char c, int count)
{
	while (count-- > 0)
	{
		if (print_char(output, c) == -1)
		{
			output->length = -1;
			return (-1);
		}
	}
	return (0);
}

int	print_str(t_print *output, const char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (print_char(output, str[i]) == -1)
		{
			output->length = -1;
			return (-1);
		}
		i++;
	}
	return (0);
}

int	print_nbr(t_print *output)
{
	int	i;

	i = output->digit_count;
	while (--i >= 0)
	{
		if (print_char(output, output->digits[i]) == -1)
		{
			output->length = -1;
			return (-1);
		}
	}
	return (0);
}

void	setup_hex_nbr_pad(t_print *output)
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
}
