/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matvivan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:19:46 by matvivan          #+#    #+#             */
/*   Updated: 2020/09/30 19:32:22 by matvivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	register unsigned char *bc;
	register unsigned char cc;

	bc = (unsigned char *)b;
	cc = (unsigned char)c;
	while (len)
		bc[--len] = cc;
	return (b);
}
