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

	bool	f_left;
	bool	f_zero;
	bool	f_hash;
	bool	f_plus;
	bool	f_space;

	int		width;
	int		precision;
	bool	has_prec;

	int		zero_pad;
	int		pad_len;
	char	pad_char;

	char	digits[32];
	int		digit_count;
	char	sign_char;
	int		prefix_len;
	char	hex_prefix[2];

	int		total_len;
	int		str_len;
	char	*temp;
}	t_print;

int		ft_printf(const char *format, ...);

void	format_chr(t_print *output, int chr);
void	format_str(t_print *output, char *str);
void	format_nbr(t_print *output, long val);
void	format_hex(t_print *output, unsigned long hex, char spec);

bool	print_char(t_print *output, char c);
bool	print_chars(t_print *output, char c, int count);
bool	print_str(t_print *output, const char *str, int len);
bool	print_nbr(t_print *output);
void	calculate_pad(t_print *output);

#endif