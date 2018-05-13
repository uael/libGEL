#ifndef GEL_SPHERE_H
# define GEL_SPHERE_H

# include "gel/math/vector.h"
# include "gel/math/matrix.h"
# include "gel/geometry/frustrum.h"
# include "gel/geometry/plane.h"

typedef struct s_sphere
{
    t_vec3     center;
    float       radius;
}              t_sphere;

t_sphere sphere_unit();
t_sphere sphere_point();
t_sphere sphere_new(t_vec3 center, float radius);
t_sphere sphere_merge(t_sphere s1, t_sphere s2);
t_sphere sphere_merge_many(t_sphere* s, int count);
t_sphere sphere_transform(t_sphere s, t_mat4 world);
t_sphere sphere_translate(t_sphere s, t_vec3 x);
t_sphere sphere_scale(t_sphere s, float x);
t_sphere sphere_transform_space(t_sphere s, t_mat3 space);

t_sphere sphere_of_box(t_box bb);
t_sphere sphere_of_frustum(t_frustum f);

bool sphere_inside_box(t_sphere s, t_box b);
bool sphere_outside_box(t_sphere s, t_box b);
bool sphere_intersects_box(t_sphere s, t_box b);

bool sphere_inside_frustum(t_sphere s, t_frustum f);
bool sphere_outside_frustum(t_sphere s, t_frustum f);
bool sphere_intersects_frustum(t_sphere s, t_frustum f);

bool sphere_outside_sphere(t_sphere s1, t_sphere s2);
bool sphere_inside_sphere(t_sphere s1, t_sphere s2);
bool sphere_intersects_sphere(t_sphere s1, t_sphere s2);

bool point_inside_sphere(t_sphere s, t_vec3 point);
bool point_outside_sphere(t_sphere s, t_vec3 point);
bool point_intersects_sphere(t_sphere s, t_vec3 point);

bool line_inside_sphere(t_sphere s, t_vec3 start, t_vec3 end);
bool line_outside_sphere(t_sphere s, t_vec3 start, t_vec3 end);
bool line_intersects_sphere(t_sphere s, t_vec3 start, t_vec3 end);

bool sphere_inside_plane(t_sphere s, t_plane p);
bool sphere_outside_plane(t_sphere s, t_plane p);
bool sphere_intersects_plane(t_sphere s, t_plane p);

bool point_swept_inside_sphere(t_sphere s, t_vec3 v, t_vec3 point);
bool point_swept_outside_sphere(t_sphere s, t_vec3 v, t_vec3 point);
bool point_swept_intersects_sphere(t_sphere s, t_vec3 v, t_vec3 point);

bool sphere_swept_inside_plane(t_sphere s, t_vec3 v, t_plane p);
bool sphere_swept_outside_plane(t_sphere s, t_vec3 v, t_plane p);
bool sphere_swept_intersects_plane(t_sphere s, t_vec3 v, t_plane p);

bool sphere_swept_outside_sphere(t_sphere s1, t_vec3 v, t_sphere s2);
bool sphere_swept_inside_sphere(t_sphere s1, t_vec3 v, t_sphere s2);
bool sphere_swept_intersects_sphere(t_sphere s1, t_vec3 v, t_sphere s2);

bool point_inside_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2);
bool sphere_intersects_face(t_sphere s, t_vec3 v0, t_vec3 v1, t_vec3 v2, t_vec3 norm);


#endif
