/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:23:52 by pamela            #+#    #+#             */
/*   Updated: 2024/04/25 18:46:55 by pamela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
This function calculates the number of space characters needed for padding
before the string. It considers the width and precision values specified in 
the t_flags structure. If precision is specified and is less than the length 
of the string, it calculates padding spaces based on the precision value. 
Otherwise, it calculates padding spaces based on the length of the string.
*/
static void	set_str_padding_spaces(t_flags *data, char *s)
{
	int	len;

	len = ft_strlen(s);
	if (data->width_value > 0)
	{
		if (data->precision_value >= 0)
		{
			if (data->precision_value > len)
			{
				data->padding_spaces = data->width_value - len;
			}
			else if (data->precision_value < len)
			{
				data->padding_spaces = data->width_value - \
						data->precision_value;
			}
		}
		else
		{
			data->padding_spaces = data->width_value - len;
		}
	}
}

/*
* [0+ #] 
 *  
 *	I care about these:
 *  	[-]   [width]    [.precision]
 This function displays the string with proper padding spaces.
 If the string is NULL, it defaults to "(null)". It first calculates 
 the padding spaces using set_str_padding_spaces. Depending on whether 
 left justification is enabled, it either displays the string followed 
 by padding spaces, or padding spaces followed by the string
*/
void	ft_display_str(t_flags *data, char *s)
{
	if (s == NULL)
		s = "(null)";
	set_str_padding_spaces(data, s);
	if (data->left_justified)
	{
		if (data->precision_value >= 0)
			ft_putstr_n(s, data->precision_value, &(data->chars_written));
		else
			ft_putstr_n(s, ft_strlen(s), &(data->chars_written));
		ft_putchar_n(' ', data->padding_spaces, &(data->chars_written));
	}
	else
	{
		ft_putchar_n(' ', data->padding_spaces, &(data->chars_written));
		if (data->precision_value >= 0)
			ft_putstr_n(s, data->precision_value, &(data->chars_written));
		else
			ft_putstr_n(s, ft_strlen(s), &(data->chars_written));
	}
}
