/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiquet <jocelyn.piquet1998@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:39:13 by jpiquet           #+#    #+#             */
/*   Updated: 2024/11/13 12:36:40 by jpiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	int	low;

	low = 0;
	if (c >= 'A' && c <= 'Z')
	{
		low = c + 32;
		return (low);
	}
	else
		return (c);
}
