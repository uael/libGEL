/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gel/math/vector.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEL_MATH_VECTOR_H
# define GEL_MATH_VECTOR_H

# include <stdbool.h>

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

extern t_v2		v2(float x, float y);
extern t_v2		v2zero(void);
extern t_v2		v2one(void);
extern t_v2		v2add(t_v2 v1, t_v2 v2);
extern t_v2		v2sub(t_v2 v1, t_v2 v2);
extern t_v2		v2mul(t_v2 v, float fac);
extern t_v2		v2mul_vec2(t_v2 v1, t_v2 v2);
extern t_v2		v2div(t_v2 v, float fac);
extern t_v2		v2div_vec2(t_v2 v1, t_v2 v2);
extern t_v2		v2pow(t_v2 v, float exp);
extern t_v2		v2neg(t_v2 v);
extern t_v2		v2abs(t_v2 v);
extern t_v2		v2floor(t_v2 v);
extern t_v2		v2fmod(t_v2 v, float val);
extern t_v2		v2max(t_v2 v, float x);
extern t_v2		v2min(t_v2 v, float x);
extern t_v2		v2clamp(t_v2 v, float b, float t);
extern bool		v2equ(t_v2 v1, t_v2 v2);
extern float	v2dot(t_v2 v1, t_v2 v2);
extern float	v2length_sqrd(t_v2 v);
extern float	v2length(t_v2 v);
extern float	v2dist_sqrd(t_v2 v1, t_v2 v2);
extern float	v2dist(t_v2 v1, t_v2 v2);
extern float	v2dist_manhattan(t_v2 v1, t_v2 v2);
extern t_v2		v2normalize(t_v2 v);
extern t_v2		v2reflect(t_v2 v1, t_v2 v2);
extern t_v2		v2from_string(char *s);
extern void		v2print(t_v2 v);
extern void		v2to_array(t_v2 v, float *out);
extern int		v2hash(t_v2 v);
extern int		v2mix_hash(t_v2 v);
extern t_v2		v2saturate(t_v2 v);
extern t_v2		v2lerp(t_v2 v1, t_v2 v2, float amount);
extern t_v2		v2smoothstep(t_v2 v1, t_v2 v2, float amount);
extern t_v2		v2smootherstep(t_v2 v1, t_v2 v2, float amount);

#endif
