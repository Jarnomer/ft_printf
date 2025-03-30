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
# include <stdbool.h>

# define HEXLOW	"0123456789abcdef"
# define HEXUPP	"0123456789ABCDEF"
# define SPECS	"cspdiuxX%"
# define FLAGS	"-0.# +"

typedef struct s_print
{
	bool	error;
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
	int		total_len;
	int		str_len;
	char	*temp;

	unsigned long	abs_val;
	char			sign_char;
	int				has_sign;
}	t_print;

int		ft_printf(const char *format, ...);
void	format_chr(t_print *output, int chr);
void	format_str(t_print *output, char *str);
void	format_nbr(t_print *output, long val);
void	format_hex(t_print *output, unsigned long hex, char spec);

#endif