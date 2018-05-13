#ifndef GEL_TRIANGLE_H
# define GEL_TRIANGLE_H

# include "gel/math/vector.h"
# include "gel/geometry/vertex.h"

t_vec3 triangle_tangent(t_vertex v1, t_vertex v2, t_vertex v3);
t_vec3 triangle_binormal(t_vertex v1, t_vertex v2, t_vertex v3);
t_vec3 triangle_normal(t_vertex v1, t_vertex v2, t_vertex v3);
t_vec3 triangle_random_position(t_vertex v1, t_vertex v2, t_vertex v3);
float triangle_area(t_vertex v1, t_vertex v2, t_vertex v3);

float triangle_difference_u(t_vertex v1, t_vertex v2, t_vertex v3);
float triangle_difference_v(t_vertex v1, t_vertex v2, t_vertex v3);

t_vertex triangle_random_position_interpolation(t_vertex v1, t_vertex v2, t_vertex v3);

#endif
