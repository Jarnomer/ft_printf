/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:48:31 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 17:55:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *str)
{
	size_t	num;
	int		sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		++str;
	if (*str == '-' || *str == '+')
		sign = ',' - *str++;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str++ - '0';
		if (num > LONG_MAX && sign < 0)
			return (0);
		else if (num > LONG_MAX && sign > 0)
			return (-1);
	}
	return ((int)num * sign);
}
