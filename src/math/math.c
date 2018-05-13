/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/clamp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/math.h>

inline float	clampf(float x, float bottom, float top)
{
	x = fmaxf(x, bottom);
	x = fminf(x, top);
	return (x);
}
