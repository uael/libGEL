/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/mat3_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gel/math/matrix.h>

inline void		mat3cpy(t_mat3 a, t_mat3 const b)
{
	a[0][0] = b[0][0];
	a[0][1] = b[0][1];
	a[0][2] = b[0][2];
	a[1][0] = b[1][0];
	a[1][1] = b[1][1];
	a[1][2] = b[1][2];
	a[2][0] = b[2][0];
	a[2][1] = b[2][1];
	a[2][2] = b[2][2];
}

inline void		mat3scale(t_mat3 a, t_vec3 const b)
{
	mat3id(a);
	a[0][0] = b[0];
	a[1][1] = b[1];
	a[2][2] = b[2];
}

inline void		mat3mul(t_mat3 a, t_mat3 const b)
{
	t_vec3 v;
	
	vec3cpy(v, a[0]);
	a[0][0] = (v[0] * b[0][0]) + (v[1] * b[1][0]) + (v[2] * b[2][0]);
	a[0][1] = (v[0] * b[0][1]) + (v[1] * b[1][1]) + (v[2] * b[2][1]);
	a[0][2] = (v[0] * b[0][2]) + (v[1] * b[1][2]) + (v[2] * b[2][2]);
	vec3cpy(v, a[1]);
	a[1][0] = (v[0] * b[0][0]) + (v[1] * b[1][0]) + (v[2] * b[2][0]);
	a[1][1] = (v[0] * b[0][1]) + (v[1] * b[1][1]) + (v[2] * b[2][1]);
	a[1][2] = (v[0] * b[0][2]) + (v[1] * b[1][2]) + (v[2] * b[2][2]);
	vec3cpy(v, a[2]);
	a[2][0] = (v[0] * b[0][0]) + (v[1] * b[1][0]) + (v[2] * b[2][0]);
	a[2][1] = (v[0] * b[0][1]) + (v[1] * b[1][1]) + (v[2] * b[2][1]);
	a[2][2] = (v[0] * b[0][2]) + (v[1] * b[1][2]) + (v[2] * b[2][2]);
}

inline void		mat3mulv(t_vec3 a, t_mat3 const m)
{
	t_vec3 v;
	
	vec3cpy(v, a);
	a[0] = (m[0][0] * v[0]) + (m[0][1] * v[1]) + (m[0][2] * v[2]);
	a[1] = (m[1][0] * v[0]) + (m[1][1] * v[1]) + (m[1][2] * v[2]);
	a[2] = (m[2][0] * v[0]) + (m[2][1] * v[1]) + (m[2][2] * v[2]);
}

inline void		mat3id(t_mat3 a)
{
	a[0][0] = 1.0f;
	a[0][1] = 0.0f;
	a[0][2] = 0.0f;
	a[1][0] = 0.0f;
	a[1][1] = 1.0f;
	a[1][2] = 0.0f;
	a[2][0] = 0.0f;
	a[2][1] = 0.0f;
	a[2][2] = 1.0f;
}

inline void		mat3zero(t_mat3 a)
{
	a[0][0] = 0.0f;
	a[0][1] = 0.0f;
	a[0][2] = 0.0f;
	a[1][0] = 0.0f;
	a[1][1] = 0.0f;
	a[1][2] = 0.0f;
	a[2][0] = 0.0f;
	a[2][1] = 0.0f;
	a[2][2] = 0.0f;
}

inline void		mat3inv(t_mat3 a)
{
	float	f;
	t_mat3	m;
	
	f = 1.0f / mat3det(a);
	mat3cpy(m, a);
	a[0][0] = f * mat2det((t_mat2 const){ m[1][1], m[1][2], m[2][1], m[2][2] });
	a[0][1] = f * mat2det((t_mat2 const){ m[0][2], m[0][1], m[2][2], m[2][1] });
	a[0][2] = f * mat2det((t_mat2 const){ m[0][1], m[0][2], m[1][1], m[1][2] });
	a[1][0] = f * mat2det((t_mat2 const){ m[1][2], m[1][0], m[2][2], m[2][0] });
	a[1][1] = f * mat2det((t_mat2 const){ m[0][0], m[0][2], m[2][0], m[2][2] });
	a[1][2] = f * mat2det((t_mat2 const){ m[0][2], m[0][0], m[1][2], m[1][0] });
	a[2][0] = f * mat2det((t_mat2 const){ m[1][0], m[1][1], m[2][0], m[2][1] });
	a[2][1] = f * mat2det((t_mat2 const){ m[0][1], m[0][0], m[2][1], m[2][0] });
	a[2][2] = f * mat2det((t_mat2 const){ m[0][0], m[0][1], m[1][0], m[1][1] });
}

inline void		mat3tra(t_mat3 a)
{
	float f;
	
	f = a[0][1];
	a[0][1] = a[1][0];
	a[1][0] = f;
	f = a[0][2];
	a[0][2] = a[2][0];
	a[2][0] = f;
	f = a[1][2];
	a[1][2] = a[2][1];
	a[2][1] = f;
}

inline float	mat3det(t_mat3 const a)
{
	return ((a[0][0] * a[1][1] * a[2][2]) + (a[0][1] * a[1][2] * a[2][0])
		+ (a[0][2] * a[1][0] * a[2][1]) - (a[0][2] * a[1][1] * a[2][0])
		- (a[0][1] * a[1][0] * a[2][2]) - (a[0][0] * a[1][2] * a[2][1]));
}

inline void		mat3rot(t_mat3 a, t_vec3 const axis, float deg)
{
	float c;
	float s;
	float nc;
	
	c = cosf(deg);
	s = sinf(deg);
	nc = 1 - c;
	a[0][0] = axis[0] * axis[0] * nc + c;
	a[0][1] = axis[0] * axis[1] * nc - axis[2] * s;
	a[0][2] = axis[0] * axis[2] * nc + axis[1] * s;
	a[1][0] = axis[1] * axis[0] * nc + axis[2] * s;
	a[1][1] = axis[1] * axis[1] * nc + c;
	a[1][2] = axis[1] * axis[2] * nc - axis[0] * s;
	a[2][0] = axis[2] * axis[0] * nc - axis[1] * s;
	a[2][1] = axis[2] * axis[1] * nc + axis[0] * s;
	a[2][2] = axis[2] * axis[2] * nc + c;
}
