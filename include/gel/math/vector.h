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

# include "math.h"

typedef float	t_vec2[2];

extern void		vec2cpy(t_vec2 a, t_vec2 const b);
extern void		vec2add(t_vec2 a, t_vec2 const b);
extern void		vec2sub(t_vec2 a, t_vec2 const b);
extern void		vec2mul(t_vec2 a, t_vec2 const b);
extern void		vec2div(t_vec2 a, float fac);
extern void		vec2pow(t_vec2 a, float exp);
extern void		vec2min(t_vec2 a, float x);
extern void		vec2max(t_vec2 a, float x);
extern void		vec2fmod(t_vec2 a, float val);
extern void		vec2scale(t_vec2 a, float fac);
extern void		vec2clamp(t_vec2 a, float bottom, float top);
extern void		vec2neg(t_vec2 a);
extern void		vec2abs(t_vec2 a);
extern void		vec2norm(t_vec2 a);
extern void		vec2floor(t_vec2 a);
extern float	vec2dot(t_vec2 const a, t_vec2 const b);
extern float	vec2len(t_vec2 const a);

typedef float	t_vec3[3];

extern void		vec3cpy(t_vec3 a, t_vec3 const b);
extern void		vec3add(t_vec3 a, t_vec3 const b);
extern void		vec3sub(t_vec3 a, t_vec3 const b);
extern void		vec3mul(t_vec3 a, t_vec3 const b);
extern void		vec3div(t_vec3 a, float fac);
extern void		vec3pow(t_vec3 a, float exp);
extern void		vec3min(t_vec3 a, float x);
extern void		vec3max(t_vec3 a, float x);
extern void		vec3fmod(t_vec3 a, float val);
extern void		vec3scale(t_vec3 a, float fac);
extern void		vec3clamp(t_vec3 a, float bottom, float top);
extern void		vec3neg(t_vec3 a);
extern void		vec3abs(t_vec3 a);
extern void		vec3norm(t_vec3 a);
extern void		vec3floor(t_vec3 a);
extern float	vec3dot(t_vec3 const a, t_vec3 const b);
extern float	vec3len(t_vec3 const a);

typedef float	t_vec4[4];

extern void		vec4cpy(t_vec4 a, t_vec4 const b);
extern void		vec4add(t_vec4 a, t_vec4 const b);
extern void		vec4sub(t_vec4 a, t_vec4 const b);
extern void		vec4mul(t_vec4 a, t_vec4 const b);
extern void		vec4div(t_vec4 a, float fac);
extern void		vec4pow(t_vec4 a, float exp);
extern void		vec4min(t_vec4 a, float x);
extern void		vec4max(t_vec4 a, float x);
extern void		vec4fmod(t_vec4 a, float val);
extern void		vec4scale(t_vec4 a, float fac);
extern void		vec4clamp(t_vec4 a, float bottom, float top);
extern void		vec4neg(t_vec4 a);
extern void		vec4abs(t_vec4 a);
extern void		vec4norm(t_vec4 a);
extern void		vec4floor(t_vec4 a);
extern float	vec4dot(t_vec4 const a, t_vec4 const b);
extern float	vec4len(t_vec4 const a);

#endif
