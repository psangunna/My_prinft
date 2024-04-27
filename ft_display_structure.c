/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_structure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:52:34 by pamela            #+#    #+#             */
/*   Updated: 2024/04/27 14:52:38 by pamela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
This function processes integer and pointer types.
If the specifier is 'd' or 'i', it handles signed integers, checking for 
negativity and passing the digit to ft_display_digit for display. 
For 'x', 'X', and 'u' specifiers, it handles unsigned integers. 
For the 'p' specifier (pointer), it treats the argument as a pointer 
and displays it.
*/
static void	treat_digit(t_flags *data, va_list *args)
{
	char			specifier;
	t_type_digit	values;

	specifier = data->specifier;
	if ('d' == specifier || 'i' == specifier)
	{
		data->signed_value = 1;
		values.sig_value = (long)(va_arg(*args, int));
		if (values.sig_value < 0)
			data->is_negative = 1;
		ft_display_digit(data, values);
	}
	else if ('x' == specifier || 'X' == specifier || 'u' == specifier)
	{
		values.unsig_value = (unsigned long)(va_arg(*args, unsigned int));
		ft_display_digit(data, values);
	}
	else if ('p' == specifier)
	{
		values.unsig_value = (unsigned long)(va_arg(*args, void *));
		ft_display_digit(data, values);
	}
}

/*
This function determines the type of data to display based on the format 
specifier. If the specifier is '%', it displays a '%' character. For 'c',
it displays a single character. For 's', it displays a string. If the 
specifier corresponds to a digit or pointer type ('d', 'i', 'u', 'x', 'X',
'p'), it calls treat_digit to handle the display. Otherwise, it writes the
specifier directly to the output.
*/
void	ft_display_structure(t_flags *data, va_list *args)
{
	char	specifier;

	specifier = data->specifier;
	if ('%' == specifier)
		ft_display_char(data, '%');
	else if ('c' == specifier)
		ft_display_char(data, va_arg(*args, int));
	else if ('s' == specifier)
		ft_display_str(data, va_arg(*args, char *));
	else if (ft_strchr((const char *)"diupxX", data->specifier))
	{
		treat_digit(data, args);
	}
	else
		write(1, &specifier, 1);
}
