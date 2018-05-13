/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/vec2_2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/vector.h>

inline void		vec2pow(t_vec2 a, float exp)
{
	a[0] = powf(a[0], exp);
	a[1] = powf(a[1], exp);
}

inline void		vec2min(t_vec2 a, float x)
{
	a[0] = fminf(a[0], x);
	a[1] = fminf(a[1], x);
}

inline void		vec2max(t_vec2 a, float x)
{
	a[0] = fmaxf(a[0], x);
	a[1] = fmaxf(a[1], x);
}

inline void		vec2fmod(t_vec2 a, float val)
{
	a[0] = fmodf(a[0], val);
	a[1] = fmodf(a[1], val);
}

inline void		vec2scale(t_vec2 a, float fac)
{
	a[0] *= fac;
	a[1] *= fac;
}
