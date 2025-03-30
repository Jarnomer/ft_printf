/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 23:25:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

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
	
	// Reset digit count
	output->digit_count = 0;
	
	// Special case: 0 value with 0 precision
	if (val == 0 && output->has_prec && output->precision == 0)
	{
		output->digit_count = 0;
	}
	else
	{
		// Handle special case of 0
		if (val == 0)
			output->digits[output->digit_count++] = '0';
		else
		{
			// Convert to hex digits using while loop
			unsigned long temp = val;
			while (temp > 0)
			{
				output->digits[output->digit_count++] = hex_chars[temp % 16];
				temp /= 16;
			}
		}
	}
	
	// Calculate zero padding for precision
	int zero_padding = 0;
	if (output->has_prec && output->precision > output->digit_count)
		zero_padding = output->precision - output->digit_count;
	
	// Calculate total length and width padding
	output->total_len = output->digit_count + zero_padding + prefix_len;
	output->pad_len = 0;
	if (output->width > output->total_len)
		output->pad_len = output->width - output->total_len;
	
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
		
		// Print digits using helper function
		if (!print_nbr(output))
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
		
		// Print digits using helper function
		if (!print_nbr(output))
			return;
	}
}
