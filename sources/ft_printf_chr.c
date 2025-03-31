/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static inline void	justify_right(t_print *output, int chr)
{
	if (print_chars(output, output->pad_char, output->pad_len) == -1)
		return ;
	print_char(output, chr);
}

static inline void	justify_left(t_print *output, int chr)
{
	if (print_char(output, chr) == -1)
		return ;
	print_chars(output, output->pad_char, output->pad_len);
}

void	format_chr(t_print *output, int chr)
{
	if (output->width > 1)
		output->pad_len = output->width - 1;
	if (output->f_left)
		justify_left(output, chr);
	else
		justify_right(output, chr);
}
