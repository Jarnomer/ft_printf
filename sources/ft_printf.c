/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_print	output;
	va_list	args;

	output.length = 0;
	va_start(args, format);
	while (*format)
	{
		reset_flags(&output);
		if (*format != '%')
			format_chr(&output, *format);
		else if (*++format)
		{
			parse_flags(&output, &format);
			if (ft_strchr(SPECS, *format))
				format_spec(&output, args, *format);
		}
		if (output.length == -1 || !*format)
			break ;
		format++;
	}
	va_end(args);
	return (output.length);
}
