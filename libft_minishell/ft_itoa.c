/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvamart <alvamart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:06:16 by alvamart          #+#    #+#             */
/*   Updated: 2024/09/27 17:53:28 by alvamart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit_count(long n)
{
	int	digit;

	digit = 0;
	if (n < 0)
	{
		n = -n;
		digit++;
	}
	while (n != 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static void	ft_strrev(char *result)
{
	char	temp;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(result) - 1;
	if (result[start] == '-')
		start++;
	while (end > start && result[start])
	{
		temp = result[start];
		result[start] = result[end];
		result[end] = temp;
		end--;
		start++;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;

	result = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = malloc(ft_digit_count(n) + 1);
	if (!result)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		n = -n;
		result[i++] = '-';
	}
	while (n)
	{
		result[i++] = (n % 10) + '0';
		n = n / 10;
	}
	result[i] = '\0';
	ft_strrev(result);
	return (result);
}
