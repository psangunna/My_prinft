/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_digit_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanguna <psanguna@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:10:27 by psanguna          #+#    #+#             */
/*   Updated: 2024/05/07 16:10:31 by psanguna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/*
 * Set zeros to pad
 * Spaces are in function of zeros
 * so i will count zeros before hand
 * 
This function adds the '0x' or '0X' prefix before hexadecimal numbers or
pointers if the hash flag ('#') is set.
*/
static void	set_0x(t_format *data)
{
	if ((ft_strchr((const char *)"xX", data->specifier) && \
			data->hash && data->temp[0] != '0') || \
			(data->specifier == 'p' && data->no_value != 1))
	{
		if (data->upper_case)
			ft_putstr_n("0X", 2, &(data->chars_written));
		else
			ft_putstr_n("0x", 2, &(data->chars_written));
	}
}

/*
This function handles the display of signs for numbers. 
If the number is hexadecimal, it calls put_0x to add the prefix. 
If the number is signed, it displays the negative sign for negative numbers, 
or '+' for positive numbers if the plus flag ('+') is set, or space padding 
if the space flag (' ') is set.
*/
static void	put_sign(t_format *data)
{
	if (data->base == 16)
		set_0x(data);
	else if (data->signed_value)
	{
		if (data->is_negative)
			ft_putchar_n('-', 1, &(data->chars_written));
		else if (!data->is_negative)
		{
			if (data->plus)
				ft_putchar_n('+', 1, &(data->chars_written));
			else if (!data->plus && data->space)
				ft_putchar_n(' ', 1, &(data->chars_written));
		}
	}
}

/*
This function orchestrates the display of digits. It first converts the 
integer value to a string representation using ft_itoa_base, then calculates
zero padding and space padding using ft_set_padding_zeros and 
ft_set_padding_spaces, respectively. Depending on whether left justification 
is enabled, it then displays the sign, zero padding, the digit itself, and 
finally space padding.
*/
void	ft_display_digit(t_format *data, t_type_digit values)
{
	if (data->no_value == 0)
		ft_itoa_base(data, values);
	ft_set_padding_zeros(data);
	ft_set_padding_spaces(data);
	if (data->left_justified)
	{
		put_sign(data);
		ft_putchar_n('0', data->padding_zeros, &(data->chars_written));
		ft_putstr_n(data->temp, data->nbr_len, &(data->chars_written));
		ft_putchar_n(' ', data->padding_spaces, &(data->chars_written));
	}
	else
	{
		ft_putchar_n(' ', data->padding_spaces, &(data->chars_written));
		put_sign(data);
		ft_putchar_n('0', data->padding_zeros, &(data->chars_written));
		ft_putstr_n(data->temp, data->nbr_len, &(data->chars_written));
	}
}
