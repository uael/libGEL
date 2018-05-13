#ifndef GEL_BOX_H
# define GEL_BOX_H

# include "gel/math/vector.h"
# include "gel/math/matrice.h"

typedef struct  s_box
{
    t_plane     top;
    t_plane     bottom;
    t_plane     left;
    t_plane     right;
    t_plane     front;
    t_plane     back;
}               t_box;

t_box           box_new(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);
t_box           box_sphere(t_vec3 center, float radius);
t_box           box_merge(t_box b1, t_box b2);
t_box           box_transform(t_box b1, t_mat4 world, t_mat3 world_normal);
t_box           box_invert(t_box b);
t_box           box_invert_depth(t_box b);
t_box           box_invert_width(t_box b);
t_box           box_invert_height(t_box b);

bool            point_inside_box(t_vec3 point, t_box b);
bool            point_outside_box(t_vec3 point, t_box b);
bool            point_intersects_box(t_vec3 point, t_box b);

#endif
