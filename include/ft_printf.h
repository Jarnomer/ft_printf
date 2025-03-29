/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:57:14 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/08 08:05:46 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/include/libft.h"

# include <stdarg.h>

# define HEXLOW	"0123456789abcdef"
# define HEXUPP	"0123456789ABCDEF"
# define SPECS	"cspdiuxX%"
# define FLAGS	"-0.# +"

typedef struct s_print
{
	int		length;
	int		result;

	int		f_minus;
	int		f_zero;
	int		f_hash;
	int		f_plus;
	int		f_space;

	int		width;
	int		precision;
	int		has_prec;

	char	pad_char;
	int		pad_len;
	int		is_negative;
	int		sign_offset;
	int		calc_len;

	char	*temp;
	long	abs_val;
}	t_print;

int		ft_printf(const char *format, ...);
void	format_chr(t_print *output, int chr);
void	format_str(t_print *output, char *str);
void	format_int(t_print *output, long val);
void	format_hex(t_print *output, unsigned long hex, char spec);
char	*handle_precision(t_print *output, char *str, long val, char spec);
void	parse_width_prec(t_print *output, const char **format);
void	apply_prefix(t_print *output, long val, char spec);
void	apply_width(t_print *output, char *str);

#endif