/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flg2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/29 12:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*handle_str_prec(t_print *output, char *str)
{
	if (output->has_prec && output->precision < (int)ft_strlen(str))
		return (ft_substr(str, 0, output->precision));
	return (ft_strdup(str));
}

char	*handle_num_prec(t_print *output, char *str, long val, int is_neg)
{
	char	*result;
	int		len;

	len = ft_strlen(str);
	if (output->has_prec && output->precision == 0 && val == 0)
		return (ft_strdup(""));
	if (output->has_prec && output->precision > len - is_neg)
	{
		result = ft_calloc(output->precision + is_neg + 1, sizeof(char));
		if (!result)
			return (NULL);
		if (is_neg)
			result[0] = '-';
		ft_memset(result + is_neg, '0', output->precision - len + is_neg);
		ft_strcpy(result + output->precision - len + is_neg * 2, 
			str + is_neg);
		free(str);
		return (result);
	}
	return (str);
}

char	*handle_precision(t_print *output, char *str, long val, char spec)
{
	int	is_negative;
	
	if (!str)
		return (NULL);
	
	if (spec == 's')
		return (handle_str_prec(output, str));
	
	is_negative = (val < 0 && (spec == 'd' || spec == 'i'));
	return (handle_num_prec(output, str, val, is_negative));
}

void	apply_right_padding(t_print *output, char padding, int pad_len)
{
	while (pad_len-- > 0)
		format_chr(output, padding);
}

void	apply_width(t_print *output, char *str, int len)
{
	char	padding;
	int		pad_len;
	
	if (!str || output->width <= len)
		return ;
	
	padding = (output->f_zero && !output->has_prec) ? '0' : ' ';
	pad_len = output->width - len;
	
	if (output->f_minus)
	{
		output->result = ft_putstr_fd(str, 1);
		apply_right_padding(output, ' ', pad_len);
	}
	else
	{
		apply_right_padding(output, padding, pad_len);
		output->result = ft_putstr_fd(str, 1);
	}
	
	if (output->result == -1)
		output->length = -1;
	else
		output->length += output->result;
}
