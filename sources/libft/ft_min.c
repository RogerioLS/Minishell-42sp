/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:21:35 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:54:19 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

signed int	ft_min(signed int valA, signed int valB)
{
	return (valA * (valA <= valB) + valB * (valB < valA));
}
