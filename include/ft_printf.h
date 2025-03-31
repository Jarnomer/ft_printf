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
# define FLAGS	"-0# +"

typedef struct s_print
{
	int		length;

	bool	f_left;
	bool	f_zero;
	bool	f_hash;
	bool	f_plus;
	bool	f_space;

	int		width;
	int		precision;
	bool	has_prec;
	int		pad_len;
	char	pad_char;

	char	digits[32];
	int		digit_count;
	int		zero_pad;
	char	sign_char;
	int		prefix_len;
	char	hex_prefix[2];
}	t_print;

int		ft_printf(const char *format, ...);

void	format_chr(t_print *output, int chr);
void	format_str(t_print *output, char *str);
void	format_nbr(t_print *output, long val);
void	format_hex(t_print *output, unsigned long hex, char spec);

int		print_char(t_print *output, char c);
int		print_chars(t_print *output, char c, int count);
int		print_str(t_print *output, const char *str, int len);
int		print_nbr(t_print *output);
void	setup_hex_nbr_pad(t_print *output);

#endif