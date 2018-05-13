#ifndef GEL_PLANE_H
# define GEL_PLANE_H

# include "gel/math/vector.h"
# include "gel/math/matrice.h"

typedef struct  s_plane
{
    t_vec3      direction;
    t_vec3      position;
}               t_plane;

t_plane         plane_new(t_vec3 position, t_vec3 direction);
t_plane         plane_transform(t_plane p, t_mat4 world, t_mat3 world_normal);
t_plane         plane_transform_space(t_plane p, t_mat3 space, t_mat3 space_normal);
float           plane_distance(t_plane p, t_vec3 point);
bool            point_inside_plane(t_vec3 point, t_plane p);
bool            point_outside_plane(t_vec3 point, t_plane p);
bool            point_intersects_plane(t_vec3 point, t_plane p);
bool            point_swept_inside_plane(t_vec3 point, t_vec3 v, t_plane p);
bool            point_swept_outside_plane(t_vec3 point, t_vec3 v, t_plane p);
bool            point_swept_intersects_plane(t_vec3 point, t_vec3 v, t_plane p);
t_vec3          plane_closest(t_plane p, t_vec3 v);
t_vec3          plane_project(t_plane p, t_vec3 v);

#endif
