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

static inline void	justify_right(t_print *output, char *str, int len)
{
	if (print_chars(output, output->pad_char, output->pad_len) == -1)
		return ;
	print_str(output, str, len);
}

static inline void	justify_left(t_print *output, char *str, int len)
{
	if (print_str(output, str, len) == -1)
		return ;
	print_chars(output, output->pad_char, output->pad_len);
}

static inline int	parse_prefix(t_print *output, char *str, int len)
{
	if (output->has_prec)
	{
		if (output->precision == 0)
			return (0);
		else if (!output->precision || output->precision < len)
		{
			if (!ft_strcmp(str, "(null)") && output->precision < 6)
				return (0);
			else
				return (output->precision);
		}
	}
	return (len);
}

void	format_str(t_print *output, char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	len = parse_prefix(output, str, len);
	if (output->width > len)
		output->pad_len = output->width - len;
	if (output->f_left)
		justify_left(output, str, len);
	else
		justify_right(output, str, len);
}
