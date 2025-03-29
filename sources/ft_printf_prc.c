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

static char	*handle_str_prec(t_print *output, char *str)
{
	if (output->has_prec && output->precision < (int)ft_strlen(str))
		return (ft_substr(str, 0, output->precision));
	return (ft_strdup(str));
}

static char	*handle_num_prec(t_print *output, char *str, long val)
{
	char	*result;

	output->calc_len = ft_strlen(str);
	if (output->has_prec && output->precision == 0 && val == 0)
		return (ft_strdup(""));
	if (output->has_prec && output->precision > output->calc_len - output->is_negative)
	{
		result = ft_calloc(output->precision + output->is_negative + 1, sizeof(char));
		if (!result)
			return (NULL);
		if (output->is_negative)
			result[0] = '-';
		ft_memset(result + output->is_negative, '0', 
			output->precision - output->calc_len + output->is_negative);
		ft_strcpy(result + output->precision - output->calc_len 
			+ output->is_negative * 2, str + output->is_negative);
		free(str);
		return (result);
	}
	return (str);
}

char	*handle_precision(t_print *output, char *str, long val, char spec)
{
	if (!str)
		return (NULL);
	if (spec == 's')
		return (handle_str_prec(output, str));
	if (val < 0 && (spec == 'd' || spec == 'i'))
		output->is_negative = 1;
	return (handle_num_prec(output, str, val));
}
