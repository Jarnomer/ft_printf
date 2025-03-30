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

static void	handle_right_justified(t_print *output)
{
	if (output->pad_char == '0' && output->has_sign)
	{
		if (!print_char(output, output->sign_char))
			return ;
		output->has_sign = 0;
	}
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
	if (output->has_sign && !print_char(output, output->sign_char))
		return ;
	if (!print_chars(output, '0', output->zero_pad))
		return ;
	if (!print_nbr(output))
		return ;
}

static void	handle_left_justified(t_print *output)
{
	if (output->has_sign && !print_char(output, output->sign_char))
		return ;
	if (!print_chars(output, '0', output->zero_pad))
		return ;
	if (!print_nbr(output))
		return ;
	if (!print_chars(output, ' ', output->pad_len))
		return ;
}

static void	setup_nbr_str(t_print *output)
{
	char	number;

	while (output->abs_val > 0)
	{
		number = output->abs_val % 10 + '0';
		output->digits[output->digit_count] = number;
		output->abs_val /= 10;
		output->digit_count++;
	}
}

static void	parse_sign(t_print *output)
{
	if (output->is_negative)
	{
		output->sign_char = '-';
		output->has_sign = 1;
	}
	else if (output->f_plus)
	{
		output->sign_char = '+';
		output->has_sign = 1;
	}
	else if (output->f_space)
	{
		output->sign_char = ' ';
		output->has_sign = 1;
	}
}

void	format_nbr(t_print *output, long val)
{
	output->is_negative = (val < 0);
	output->abs_val = ft_labs(val);
	parse_sign(output);
	if (output->abs_val == 0)
		output->digits[output->digit_count++] = '0';
	else
		setup_nbr_str(output);
	calc_pad(output);
	if (output->f_minus)
		handle_left_justified(output);
	else
		handle_right_justified(output);
}
