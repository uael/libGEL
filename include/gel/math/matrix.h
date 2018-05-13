/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gel/math/matrix.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEL_MATH_MATRIX_H
# define GEL_MATH_MATRIX_H

# include "quat.h"

typedef t_vec2	t_mat2[2];

extern void		mat2cpy(t_mat2 a, t_mat2 const b);
extern void		mat2mul(t_mat2 a, t_mat2 const b);
extern void		mat2mulv(t_vec2 a, t_mat2 const b);
extern void		mat2id(t_mat2 a);
extern void		mat2zero(t_mat2 a);
extern void		mat2inv(t_mat2 a);
extern void		mat2tra(t_mat2 a);
extern float	mat2det(t_mat2 const a);
extern void		mat2rot(t_mat2 a, float deg);

typedef t_vec3	t_mat3[3];

extern void		mat3cpy(t_mat3 a, t_mat3 const b);
extern void		mat3scale(t_mat3 a, t_vec3 const b);
extern void		mat3mul(t_mat3 a, t_mat3 const b);
extern void		mat3mulv(t_vec3 a, t_mat3 const b);
extern void		mat3id(t_mat3 a);
extern void		mat3zero(t_mat3 a);
extern void		mat3inv(t_mat3 a);
extern void		mat3tra(t_mat3 a);
extern float	mat3det(t_mat3 const a);
extern void		mat3rot(t_mat3 a, t_vec3 const axis, float deg);

typedef t_vec4	t_mat4[4];

static inline void mat4id(t_mat4 M)
{
	int i, j;
	for(i=0; i<4; ++i)
		for(j=0; j<4; ++j)
			M[i][j] = i==j ? 1.f : 0.f;
}
static inline void mat4dup(t_mat4 M, t_mat4 N)
{
	int i, j;
	for(i=0; i<4; ++i)
		for(j=0; j<4; ++j)
			M[i][j] = N[i][j];
}
static inline void mat4row(t_vec4 r, t_mat4 M, int i)
{
	int k;
	for(k=0; k<4; ++k)
		r[k] = M[k][i];
}
static inline void mat4col(t_vec4 r, t_mat4 M, int i)
{
	int k;
	for(k=0; k<4; ++k)
		r[k] = M[i][k];
}
static inline void mat4transpose(t_mat4 a)
{
	float f;

	f = a[0][1];
	a[0][1] = a[1][0];
	a[1][0] = f;
	f = a[0][2];
	a[0][2] = a[2][0];
	a[2][0] = f;
	f = a[0][3];
	a[0][3] = a[3][0];
	a[3][0] = f;
	f = a[1][2];
	a[1][2] = a[2][1];
	a[2][1] = f;
	f = a[1][3];
	a[1][3] = a[3][1];
	a[3][1] = f;
	f = a[2][3];
	a[2][3] = a[3][2];
	a[3][2] = f;
}
static inline void mat4add(t_mat4 a, t_mat4 b)
{
	int i;
	for(i=0; i<4; ++i)
		vec4add(a[i], b[i]);
}
static inline void mat4sub(t_mat4 a, t_mat4 b)
{
	int i;
	for(i=0; i<4; ++i)
		vec4sub(a[i], b[i]);
}
static inline void mat4scale(t_mat4 a, float k)
{
	int i;
	for(i=0; i<4; ++i)
		vec4scale(a[i], k);
}
static inline void mat4scale_aniso(t_mat4 M, t_mat4 a, float x, float y, float z)
{
	int i;
	vec4scale(a[0], x);
	vec4scale(a[1], y);
	vec4scale(a[2], z);
	for(i = 0; i < 4; ++i) {
		M[3][i] = a[3][i];
	}
}
static inline void mat4mul(t_mat4 M, t_mat4 a, t_mat4 b)
{
	t_mat4 temp;
	int k, r, c;
	for(c=0; c<4; ++c) for(r=0; r<4; ++r) {
			temp[c][r] = 0.f;
			for(k=0; k<4; ++k)
				temp[c][r] += a[k][r] * b[c][k];
		}
	mat4dup(M, temp);
}
static inline void mat4mul_vec4(t_vec4 r, t_mat4 M, t_vec4 v)
{
	int i, j;
	for(j=0; j<4; ++j) {
		r[j] = 0.f;
		for(i=0; i<4; ++i)
			r[j] += M[i][j] * v[i];
	}
}
static inline void mat4translate(t_mat4 T, float x, float y, float z)
{
	mat4id(T);
	T[3][0] = x;
	T[3][1] = y;
	T[3][2] = z;
}
static inline void mat4translate_in_place(t_mat4 M, float x, float y, float z)
{
	t_vec4 t = {x, y, z, 0};
	t_vec4 r;
	int i;
	for (i = 0; i < 4; ++i) {
		mat4row(r, M, i);
		M[3][i] += vec4_mul_inner(r, t);
	}
}
static inline void mat4from_vec3_mul_outer(t_mat4 M, vec3 a, vec3 b)
{
	int i, j;
	for(i=0; i<4; ++i) for(j=0; j<4; ++j)
			M[i][j] = i<3 && j<3 ? a[i] * b[j] : 0.f;
}
static inline void mat4rotate(t_mat4 R, t_mat4 M, float x, float y, float z, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	vec3 u = {x, y, z};

	if(vec3_len(u) > 1e-4) {
		t_mat4 T, C, S = {{0}};

		vec3_norm(u, u);
		mat4from_vec3_mul_outer(T, u, u);

		S[1][2] =  u[0];
		S[2][1] = -u[0];
		S[2][0] =  u[1];
		S[0][2] = -u[1];
		S[0][1] =  u[2];
		S[1][0] = -u[2];

		mat4scale(S, S, s);

		mat4identity(C);
		mat4sub(C, C, T);

		mat4scale(C, C, c);

		mat4add(T, T, C);
		mat4add(T, T, S);

		T[3][3] = 1.;
		mat4mul(R, M, T);
	} else {
		mat4dup(R, M);
	}
}
static inline void mat4rotate_X(t_mat4 Q, t_mat4 M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	t_mat4 R = {
		{1.f, 0.f, 0.f, 0.f},
		{0.f,   c,   s, 0.f},
		{0.f,  -s,   c, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};
	mat4mul(Q, M, R);
}
static inline void mat4rotate_Y(t_mat4 Q, t_mat4 M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	t_mat4 R = {
		{   c, 0.f,   s, 0.f},
		{ 0.f, 1.f, 0.f, 0.f},
		{  -s, 0.f,   c, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4mul(Q, M, R);
}
static inline void mat4rotate_Z(t_mat4 Q, t_mat4 M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	t_mat4 R = {
		{   c,   s, 0.f, 0.f},
		{  -s,   c, 0.f, 0.f},
		{ 0.f, 0.f, 1.f, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	mat4mul(Q, M, R);
}
static inline void mat4invert(t_mat4 T, t_mat4 M)
{
	float idet;
	float s[6];
	float c[6];
	s[0] = M[0][0]*M[1][1] - M[1][0]*M[0][1];
	s[1] = M[0][0]*M[1][2] - M[1][0]*M[0][2];
	s[2] = M[0][0]*M[1][3] - M[1][0]*M[0][3];
	s[3] = M[0][1]*M[1][2] - M[1][1]*M[0][2];
	s[4] = M[0][1]*M[1][3] - M[1][1]*M[0][3];
	s[5] = M[0][2]*M[1][3] - M[1][2]*M[0][3];

	c[0] = M[2][0]*M[3][1] - M[3][0]*M[2][1];
	c[1] = M[2][0]*M[3][2] - M[3][0]*M[2][2];
	c[2] = M[2][0]*M[3][3] - M[3][0]*M[2][3];
	c[3] = M[2][1]*M[3][2] - M[3][1]*M[2][2];
	c[4] = M[2][1]*M[3][3] - M[3][1]*M[2][3];
	c[5] = M[2][2]*M[3][3] - M[3][2]*M[2][3];

	/* Assumes it is invertible */
	idet = 1.0f/( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );

	T[0][0] = ( M[1][1] * c[5] - M[1][2] * c[4] + M[1][3] * c[3]) * idet;
	T[0][1] = (-M[0][1] * c[5] + M[0][2] * c[4] - M[0][3] * c[3]) * idet;
	T[0][2] = ( M[3][1] * s[5] - M[3][2] * s[4] + M[3][3] * s[3]) * idet;
	T[0][3] = (-M[2][1] * s[5] + M[2][2] * s[4] - M[2][3] * s[3]) * idet;

	T[1][0] = (-M[1][0] * c[5] + M[1][2] * c[2] - M[1][3] * c[1]) * idet;
	T[1][1] = ( M[0][0] * c[5] - M[0][2] * c[2] + M[0][3] * c[1]) * idet;
	T[1][2] = (-M[3][0] * s[5] + M[3][2] * s[2] - M[3][3] * s[1]) * idet;
	T[1][3] = ( M[2][0] * s[5] - M[2][2] * s[2] + M[2][3] * s[1]) * idet;

	T[2][0] = ( M[1][0] * c[4] - M[1][1] * c[2] + M[1][3] * c[0]) * idet;
	T[2][1] = (-M[0][0] * c[4] + M[0][1] * c[2] - M[0][3] * c[0]) * idet;
	T[2][2] = ( M[3][0] * s[4] - M[3][1] * s[2] + M[3][3] * s[0]) * idet;
	T[2][3] = (-M[2][0] * s[4] + M[2][1] * s[2] - M[2][3] * s[0]) * idet;

	T[3][0] = (-M[1][0] * c[3] + M[1][1] * c[1] - M[1][2] * c[0]) * idet;
	T[3][1] = ( M[0][0] * c[3] - M[0][1] * c[1] + M[0][2] * c[0]) * idet;
	T[3][2] = (-M[3][0] * s[3] + M[3][1] * s[1] - M[3][2] * s[0]) * idet;
	T[3][3] = ( M[2][0] * s[3] - M[2][1] * s[1] + M[2][2] * s[0]) * idet;
}
static inline void mat4orthonormalize(t_mat4 R, t_mat4 M)
{
	float s = 1.;
	vec3 h;

	mat4dup(R, M);
	vec3_norm(R[2], R[2]);

	s = vec3_mul_inner(R[1], R[2]);
	vec3_scale(h, R[2], s);
	vec3_sub(R[1], R[1], h);
	vec3_norm(R[2], R[2]);

	s = vec3_mul_inner(R[1], R[2]);
	vec3_scale(h, R[2], s);
	vec3_sub(R[1], R[1], h);
	vec3_norm(R[1], R[1]);

	s = vec3_mul_inner(R[0], R[1]);
	vec3_scale(h, R[1], s);
	vec3_sub(R[0], R[0], h);
	vec3_norm(R[0], R[0]);
}

static inline void mat4frustum(t_mat4 M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f*n/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f*n/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][0] = (r+l)/(r-l);
	M[2][1] = (t+b)/(t-b);
	M[2][2] = -(f+n)/(f-n);
	M[2][3] = -1.f;

	M[3][2] = -2.f*(f*n)/(f-n);
	M[3][0] = M[3][1] = M[3][3] = 0.f;
}
static inline void mat4ortho(t_mat4 M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f/(f-n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;

	M[3][0] = -(r+l)/(r-l);
	M[3][1] = -(t+b)/(t-b);
	M[3][2] = -(f+n)/(f-n);
	M[3][3] = 1.f;
}
static inline void mat4perspective(t_mat4 m, float y_fov, float aspect, float n, float f)
{
	/* NOTE: Degrees are an unhandy unit to work with.
	 * linmath.h uses radians for everything! */
	float const a = 1.f / (float) tan(y_fov / 2.f);

	m[0][0] = a / aspect;
	m[0][1] = 0.f;
	m[0][2] = 0.f;
	m[0][3] = 0.f;

	m[1][0] = 0.f;
	m[1][1] = a;
	m[1][2] = 0.f;
	m[1][3] = 0.f;

	m[2][0] = 0.f;
	m[2][1] = 0.f;
	m[2][2] = -((f + n) / (f - n));
	m[2][3] = -1.f;

	m[3][0] = 0.f;
	m[3][1] = 0.f;
	m[3][2] = -((2.f * f * n) / (f - n));
	m[3][3] = 0.f;
}
static inline void mat4look_at(t_mat4 m, vec3 eye, vec3 center, vec3 up)
{
	/* Adapted from Android's OpenGL Matrix.java.                        */
	/* See the OpenGL GLUT documentation for gluLookAt for a description */
	/* of the algorithm. We implement it in a straightforward way:       */

	/* TODO: The negation of of can be spared by swapping the order of
	 *       operands in the following cross products in the right way. */
	vec3 f;
	vec3 s;
	vec3 t;

	vec3_sub(f, center, eye);
	vec3_norm(f, f);

	vec3_mul_cross(s, f, up);
	vec3_norm(s, s);

	vec3_mul_cross(t, s, f);

	m[0][0] =  s[0];
	m[0][1] =  t[0];
	m[0][2] = -f[0];
	m[0][3] =   0.f;

	m[1][0] =  s[1];
	m[1][1] =  t[1];
	m[1][2] = -f[1];
	m[1][3] =   0.f;

	m[2][0] =  s[2];
	m[2][1] =  t[2];
	m[2][2] = -f[2];
	m[2][3] =   0.f;

	m[3][0] =  0.f;
	m[3][1] =  0.f;
	m[3][2] =  0.f;
	m[3][3] =  1.f;

	mat4translate_in_place(m, -eye[0], -eye[1], -eye[2]);
}

#endif
