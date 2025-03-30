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

static void	justify_right(t_print *output, int chr)
{
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
	if (!print_char(output, chr))
		return ;
}

static void	justify_left(t_print *output, int chr)
{
	if (!print_char(output, chr))
		return ;
	if (!print_chars(output, output->pad_char, output->pad_len))
		return ;
}

static void	parse_prefix(t_print *output)
{
	if (output->width > 1)
	{
		output->pad_len = output->width - 1;
		if (output->f_zero && !output->f_left)
			output->pad_char = '0';
	}
}

void	format_chr(t_print *output, int chr)
{
	parse_prefix(output);
	if (output->f_left)
		justify_left(output, chr);
	else
		justify_right(output, chr);
}
