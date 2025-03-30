/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf_fmt.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jmertane <jmertane@student.hive.fi>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/10 17:53:31 by jmertane		  #+#	#+#			 */
/*   Updated: 2024/02/06 23:24:42 by jmertane		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <ft_printf.h>

static bool print_char(t_print *output, char c)
{
	if (output->error)
		return (false);
	if (ft_putchar_fd(c, 1) == -1)
	{
		output->error = true;
		output->length = -1;
		return (false);
	}
	output->length += 1;
	return (true);
}

static bool print_chars(t_print *output, char c, int count)
{
	while (count-- > 0)
	{
		if (!print_char(output, c))
			return false;
	}
	return true;
}

static bool print_str(t_print *output, const char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (!print_char(output, str[i]))
			return false;
		i++;
	}
	return true;
}

void format_chr(t_print *output, int chr)
{
	if (output->width > 1)
	{
		output->pad_len = output->width - 1;
		if (output->f_zero && !output->f_minus)
			output->pad_char = '0';
	}
	if (output->f_minus)
	{
		if (!print_char(output, chr))
			return;
		if (!print_chars(output, ' ', output->pad_len))
			return;
	}
	else
	{
		if (!print_chars(output, output->pad_char, output->pad_len))
			return;
		if (!print_char(output, chr))
			return;
	}
}

void format_str(t_print *output, char *str)
{
	if (!str)
		str = "(null)";
	output->str_len = ft_strlen(str);
	if (output->has_prec)
	{
		if (output->precision == 0)
			output->str_len = 0;
		else if (output->precision < output->str_len)
			output->str_len = output->precision;
	}
	if (output->width > output->str_len)
		output->pad_len = output->width - output->str_len;
	if (output->f_minus)
	{
		if (!print_str(output, str, output->str_len))
			return;
		if (!print_chars(output, ' ', output->pad_len))
			return;
	}
	else
	{
		if (!print_chars(output, ' ', output->pad_len))
			return;
		if (!print_str(output, str, output->str_len))
			return;
	}
}

void format_hex(t_print *output, unsigned long val, char spec)
{
	// Special case for pointers
	if (spec == 'p' && val == 0)
	{
		format_str(output, "(nil)");
		return;
	}
	
	// Determine hex base
	const char *hex_chars = (spec == 'X') ? HEXUPP : HEXLOW;
	
	// Determine prefix
	const char *prefix = NULL;
	int prefix_len = 0;
	
	if (spec == 'p')
	{
		prefix = "0x";
		prefix_len = 2;
	}
	else if (output->f_hash && val != 0)
	{
		prefix = (spec == 'X') ? "0X" : "0x";
		prefix_len = 2;
	}
	
	// Convert to hex digits
	char digits[32];
	int digit_count = 0;
	
	// Special case: 0 value with 0 precision
	if (val == 0 && output->has_prec && output->precision == 0)
	{
		digit_count = 0; // No digits to print
	}
	else
	{
		// Handle special case of 0
		if (val == 0)
			digits[digit_count++] = '0';
			
		// Convert to hex digits
		unsigned long temp = val;
		while (temp > 0)
		{
			digits[digit_count++] = hex_chars[temp % 16];
			temp /= 16;
		}
	}
	
	// Calculate zero padding for precision
	int zero_padding = 0;
	if (output->has_prec && output->precision > digit_count)
		zero_padding = output->precision - digit_count;
	
	// Calculate total length and width padding
	output->total_len = digit_count + zero_padding + prefix_len;
	output->pad_len = (output->width > output->total_len) ? output->width - output->total_len : 0;
	
	// Determine width padding character
	output->pad_char = (output->f_zero && !output->has_prec && !output->f_minus) ? '0' : ' ';
	
	// Print according to justification
	if (output->f_minus) // Left-justified
	{
		// Print prefix
		if (prefix)
			if (!print_str(output, prefix, prefix_len))
				return;
		
		// Print precision zeros
		if (!print_chars(output, '0', zero_padding))
			return;
		
		// Print hex digits
		for (int i = digit_count - 1; i >= 0; i--)
			if (!print_char(output, digits[i]))
				return;
		
		// Print width padding spaces
		if (!print_chars(output, ' ', output->pad_len))
			return;
	}
	else // Right-justified
	{
		// If zero padding, print prefix first
		if (output->pad_char == '0' && prefix)
		{
			if (!print_str(output, prefix, prefix_len))
				return;
			prefix = NULL;
		}
		
		// Print width padding
		if (!print_chars(output, output->pad_char, output->pad_len))
			return;
		
		// Print prefix if not already printed
		if (prefix)
			if (!print_str(output, prefix, prefix_len))
				return;
		
		// Print precision zeros
		if (!print_chars(output, '0', zero_padding))
			return;
		
		// Print hex digits
		for (int i = digit_count - 1; i >= 0; i--)
			if (!print_char(output, digits[i]))
				return;
	}
}

static void	setup_nbr_sign(t_print *output, long val)
{
	output->is_negative = (val < 0);
	output->abs_val = ft_labs(val);
	if (output->is_negative)
	{
		output->sign_char = '-';
		output->has_sign = 1;
	}
	else if (output->f_plus)
	{
		output->sign_char = '+';
		output->has_sign = 1;
	}
	else if (output->f_space)
	{
		output->sign_char = ' ';
		output->has_sign = 1;
	}
}

void format_nbr(t_print *output, long val)
{
	setup_nbr_sign(output, val);
	
	char digits[32];
	int digit_count = 0;

	if (output->abs_val == 0 && output->has_prec && output->precision == 0)
		digit_count = 0;
	else
	{
		do {
			digits[digit_count++] = '0' + (output->abs_val % 10);
			output->abs_val /= 10;
		} while (output->abs_val > 0);
	}
	int zero_padding = 0;
	if (output->has_prec && output->precision > digit_count)
		zero_padding = output->precision - digit_count;
	output->total_len = digit_count + zero_padding + output->has_sign;
	if (output->width > output->total_len)
		output->pad_len = output->width - output->total_len;
	if (output->f_zero && !output->has_prec && !output->f_minus) 
		output->pad_char = '0';
	if (output->f_minus)
	{
		if (output->has_sign && !print_char(output, output->sign_char))
			return;
		if (!print_chars(output, '0', zero_padding))
			return;
		for (int i = digit_count - 1; i >= 0; i--)
			if (!print_char(output, digits[i]))
				return;
		if (!print_chars(output, ' ', output->pad_len))
			return;
	}
	else
	{
		if (output->pad_char == '0' && output->has_sign)
		{
			if (!print_char(output, output->sign_char))
				return;
			output->has_sign = 0;
		}
		if (!print_chars(output, output->pad_char, output->pad_len))
			return;
		if (output->has_sign && !print_char(output, output->sign_char))
			return;
		if (!print_chars(output, '0', zero_padding))
			return;
		for (int i = digit_count - 1; i >= 0; i--)
			if (!print_char(output, digits[i]))
				return;
	}
}
