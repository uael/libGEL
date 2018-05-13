/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec2_4.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline float	vec2dot(t_vec2 const a, t_vec2 const b)
{
	float p;

	p = 0.f;
	p += a[0] * b[0];
	p += a[1] * b[1];
	return (p);
}

inline float	vec2len(t_vec2 const a)
{
	return sqrtf(vec2dot(a, a));
}
