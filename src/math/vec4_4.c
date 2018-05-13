/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec4_4.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline float	vec4dot(t_vec4 const a, t_vec4 const b)
{
	float p;

	p = 0.f;
	p += a[0] * b[0];
	p += a[1] * b[1];
	return (p);
}

inline float	vec4len(t_vec4 const a)
{
	return sqrtf(vec4dot(a, a));
}
