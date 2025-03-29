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
	int	pad_len;
	
	if (output->width > 1)
	{
		pad_len = output->width - 1;
		if (output->f_minus)
		{
			if (ft_putchar_fd(chr, 1) == -1)
				output->length = -1;
			else
				output->length += 1;
			apply_right_padding(output, ' ', pad_len);
			return ;
		}
		else
			apply_right_padding(output, 
				(output->f_zero) ? '0' : ' ', pad_len);
	}
	if (ft_putchar_fd(chr, 1) == -1)
		output->length = -1;
	else
		output->length += 1;
}

void	format_str(t_print *output, char *str)
{
	char	*processed_str;
	int		len;
	
	if (!str)
		str = "(null)";
	processed_str = handle_precision(output, str, 0, 's');
	if (!processed_str)
	{
		output->length = -1;
		return ;
	}
	len = ft_strlen(processed_str);
	if (output->width > len)
		apply_width(output, processed_str, len);
	else
	{
		output->result = ft_putstr_fd(processed_str, 1);
		if (output->result == -1)
			output->length = -1;
		else
			output->length += output->result;
	}
	if (processed_str != str)
		free(processed_str);
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

static int	calc_int_len(t_print *output, long val, int base_len)
{
	if (val < 0 || output->f_plus || output->f_space)
		return (base_len + 1);
	return (base_len);
}

void	format_int(t_print *output, long val)
{
	char	*num_str;
	char	*processed_str;
	int		len;
	long	abs_val;
	
	abs_val = (val < 0) ? -val : val;
	num_str = ft_itoa(abs_val);
	if (!num_str)
	{
		output->length = -1;
		return ;
	}
	processed_str = handle_precision(output, num_str, val, 'd');
	if (!processed_str)
	{
		output->length = -1;
		return ;
	}
	len = calc_int_len(output, val, ft_strlen(processed_str));
	if (output->width <= len)
		print_int_with_prefix(output, val, processed_str);
	else
		format_int_width(output, val, processed_str, len);
	free(processed_str);
}
