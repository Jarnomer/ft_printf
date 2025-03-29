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
	int	length;		/* total length of output */
	int	result;		/* result of most recent operation */
	
	/* Flag tracking */
	int	f_minus;	/* left alignment */
	int	f_zero;		/* zero padding */
	int	f_hash;		/* alternate form (0x/0X) */
	int	f_plus;		/* force sign (+/-) */
	int	f_space;	/* space if no sign */
	
	/* Width and precision */
	int	width;		/* minimum field width */
	int	precision;	/* precision value */
	int	has_prec;	/* precision was specified */
}	t_print;

/* Main function */
int		ft_printf(const char *format, ...);

/* Format handlers */
void	format_chr(t_print *output, int chr);
void	format_str(t_print *output, char *str);
void	format_int(t_print *output, long val);
void	format_hex(t_print *output, unsigned long hex, char spec);
void	format_spec(t_print *output, va_list args, char spec);
void	format_int_width(t_print *output, long val, char *str, int len);

/* Flag utilities */
void	reset_flags(t_print *output);
void	parse_flags(t_print *output, const char **format);
void	parse_flag_chars(t_print *output, const char **format);
void	parse_width_prec(t_print *output, const char **format);
void	apply_prefix(t_print *output, long val, char spec);
void	apply_width(t_print *output, char *str, int len);
void	apply_right_padding(t_print *output, char padding, int pad_len);
char	*handle_precision(t_print *output, char *str, long val, char spec);
char	*handle_str_prec(t_print *output, char *str);
char	*handle_num_prec(t_print *output, char *str, long val, int is_neg);

#endif