/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:12:25 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/06 18:18:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
long	ft_labs(long n);

#endif
