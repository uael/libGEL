#include "gel/geometry.h" 

t_plane plane_new(t_vec3 position, t_vec3 direction) {
    t_plane p;
    p.position = position;
    p.direction = direction;
    return p;
}

float plane_distance(t_plane p, t_vec3 point) {
    t_vec3 v;

    vec3cpy(v, point);
    vec3sub(v, p.position);
    return vec3dot(v, p.direction);
}

t_plane plane_transform(t_plane p, t_mat4 world, t_mat3 world_normal) {
    p.position  = mat4_mul_vec3(world, p.position);
    p.direction = mat3_mul_vec3(world_normal, p.direction);
    p.direction = vec3_normalize(p.direction);
    return p;
}

t_plane plane_transform_space(t_plane p, t_mat3 space, t_mat3 space_normal) {
    p.position  = mat3_mul_vec3(space, p.position);
    p.direction = mat3_mul_vec3(space_normal, p.direction);
    p.direction = vec3_normalize(p.direction);
    return p;
}

bool point_inside_plane(t_vec3 point, t_plane p) {
    return vec3_dot(vec3_sub(point, p.position), p.direction) < 0;
}

bool point_outside_plane(t_vec3 point, t_plane p) {
    return vec3_dot(vec3_sub(point, p.position), p.direction) > 0;
}

bool point_intersects_plane(t_vec3 point, t_plane p) {
    return vec3_dot(vec3_sub(point, p.position), p.direction) == 0;
}

t_vec3 plane_project(t_plane p, t_vec3 v) {
    return vec3_sub(v, vec3_mul(p.direction, vec3_dot(v, p.direction)));
}

t_vec3 plane_closest(t_plane p, t_vec3 v) {
    return vec3_sub(v, vec3_mul(p.direction, plane_distance(p, v)));
}

bool point_swept_inside_plane(t_vec3 point, t_vec3 v, t_plane p) {

    float angle = vec3_dot(p.direction, v);
    float dist  = vec3_dot(p.direction, vec3_sub(point, p.position));

    if ( -dist <= 0.0 ) { return false; }

    return !between_or(-dist / angle, 0, 1);

}

bool point_swept_outside_plane(t_vec3 point, t_vec3 v, t_plane p) {

    float angle = vec3_dot(p.direction, v);
    float dist  = vec3_dot(p.direction, vec3_sub(point, p.position));

    if ( dist <= 0.0 ) { return false; }

    return !between_or(-dist / angle, 0, 1);

}

bool point_swept_intersects_plane(t_vec3 point, t_vec3 v, t_plane p) {

    float angle = vec3_dot(p.direction, v);
    float dist  = vec3_dot(p.direction, vec3_sub(point, p.position));

    if ( dist == 0.0 ) { return true; }

    return between_or(-dist / angle, 0, 1);

}

t_box box_new(float x_min, float x_max, float y_min, float y_max, float z_min, float z_max) {

    t_box bb;
    bb.top    = plane_new( vec3_new(0, y_max,0), vec3_new(0, 1,0));
    bb.bottom = plane_new( vec3_new(0, y_min,0), vec3_new(0,-1,0));
    bb.left   = plane_new( vec3_new( x_max,0,0), vec3_new( 1,0,0));
    bb.right  = plane_new( vec3_new( x_min,0,0), vec3_new(-1,0,0));
    bb.front  = plane_new( vec3_new(0,0, z_max), vec3_new(0,0, 1));
    bb.back   = plane_new( vec3_new(0,0, z_min), vec3_new(0,0,-1));
    return bb;

}

t_box box_sphere(t_vec3 center, float radius) {

    t_box bb;
    bb.top    = plane_new(vec3_add(center, vec3_new(0, radius,0)), vec3_new(0, 1,0));
    bb.bottom = plane_new(vec3_add(center, vec3_new(0,-radius,0)), vec3_new(0,-1,0));
    bb.left   = plane_new(vec3_add(center, vec3_new( radius,0,0)), vec3_new( 1,0,0));
    bb.right  = plane_new(vec3_add(center, vec3_new(-radius,0,0)), vec3_new(-1,0,0));
    bb.front  = plane_new(vec3_add(center, vec3_new(0,0, radius)), vec3_new(0,0, 1));
    bb.back   = plane_new(vec3_add(center, vec3_new(0,0,-radius)), vec3_new(0,0,-1));
    return bb;

}

t_box box_invert(t_box b) {
    b.front.direction  = vec3_neg(b.front.direction);
    b.back.direction   = vec3_neg(b.back.direction);
    b.left.direction   = vec3_neg(b.left.direction);
    b.right.direction  = vec3_neg(b.right.direction);
    b.top.direction    = vec3_neg(b.top.direction);
    b.bottom.direction = vec3_neg(b.bottom.direction);
    return b;
}

t_box box_invert_depth(t_box b) {
    b.front.direction = vec3_neg(b.front.direction);
    b.back.direction = vec3_neg(b.back.direction);
    return b;
}

t_box box_invert_width(t_box b) {
    b.left.direction = vec3_neg(b.left.direction);
    b.right.direction = vec3_neg(b.right.direction);
    return b;
}

t_box box_invert_height(t_box b) {
    b.top.direction = vec3_neg(b.top.direction);
    b.bottom.direction = vec3_neg(b.bottom.direction);
    return b;
}

bool point_inside_box(t_vec3 point, t_box b) {

    if (!point_inside_plane(point, b.top))    { return false; }
    if (!point_inside_plane(point, b.bottom)) { return false; }
    if (!point_inside_plane(point, b.left))   { return false; }
    if (!point_inside_plane(point, b.right))  { return false; }
    if (!point_inside_plane(point, b.front))  { return false; }
    if (!point_inside_plane(point, b.back))   { return false; }

    return true;

}

bool point_outside_box(t_vec3 point, t_box b) {
    return !(point_intersects_box(point, b) || point_inside_box(point, b));
}

bool point_intersects_box(t_vec3 point, t_box b) {

    bool in_left   = !point_outside_plane(point, b.left);
    bool in_right  = !point_outside_plane(point, b.right);
    bool in_front  = !point_outside_plane(point, b.front);
    bool in_back   = !point_outside_plane(point, b.back);
    bool in_top    = !point_outside_plane(point, b.top);
    bool in_bottom = !point_outside_plane(point, b.bottom);

    if (point_intersects_plane(point, b.top) &&
        in_left && in_right && in_front && in_back) {
        return true;
    }

    if (point_intersects_plane(point, b.bottom) &&
        in_left && in_right && in_front && in_back) {
        return true;
    }

    if (point_intersects_plane(point, b.left) &&
        in_top && in_bottom && in_front && in_back) {
        return true;
    }

    if (point_intersects_plane(point, b.right) &&
        in_top && in_bottom && in_front && in_back) {
        return true;
    }

    if (point_intersects_plane(point, b.front) &&
        in_top && in_bottom && in_left && in_right) {
        return true;
    }

    if (point_intersects_plane(point, b.back) &&
        in_top && in_bottom && in_left && in_right) {
        return true;
    }

    return false;

}

t_box box_merge(t_box b1, t_box b2) {

    float b1_x_max = b1.left.position.x;
    float b1_x_min = b1.right.position.x;
    float b1_y_max = b1.top.position.y;
    float b1_y_min = b1.bottom.position.y;
    float b1_z_max = b1.front.position.z;
    float b1_z_min = b1.back.position.z;

    float b2_x_max = b2.left.position.x;
    float b2_x_min = b2.right.position.x;
    float b2_y_max = b2.top.position.y;
    float b2_y_min = b2.bottom.position.y;
    float b2_z_max = b2.front.position.z;
    float b2_z_min = b2.back.position.z;

    float x_min = min(b1_x_min, b2_x_min);
    float x_max = max(b1_x_max, b2_x_max);
    float y_min = min(b1_y_min, b2_y_min);
    float y_max = max(b1_y_max, b2_y_max);
    float z_min = min(b1_z_min, b2_z_min);
    float z_max = max(b1_z_max, b2_z_max);

    return box_new(x_min, x_max, y_min, y_max, z_min, z_max);
}

t_box box_transform(t_box bb, t_mat4 world, t_mat3 world_normal) {

    bb.top    = plane_transform(bb.top,    world, world_normal);
    bb.bottom = plane_transform(bb.bottom, world, world_normal);
    bb.left   = plane_transform(bb.left,   world, world_normal);
    bb.right  = plane_transform(bb.right,  world, world_normal);
    bb.front  = plane_transform(bb.front,  world, world_normal);
    bb.back   = plane_transform(bb.back,   world, world_normal);

    return bb;

}

t_frustum frustum_new(t_vec3 ntr, t_vec3 ntl, t_vec3 nbr, t_vec3 nbl, t_vec3 ftr, t_vec3 ftl, t_vec3 fbr, t_vec3 fbl) {
    t_frustum f;
    f.ntr = ntr;
    f.ntl = ntl;
    f.nbr = nbr;
    f.nbl = nbl;
    f.ftr = ftr;
    f.ftl = ftl;
    f.fbr = fbr;
    f.fbl = fbl;
    return f;
}

t_frustum frustum_new_clipbox() {
    return frustum_new(
            vec3_new( 1, 1,-1), vec3_new(-1, 1,-1),
            vec3_new( 1,-1,-1), vec3_new(-1,-1,-1),
            vec3_new( 1, 1, 1), vec3_new(-1, 1, 1),
            vec3_new( 1,-1, 1), vec3_new(-1,-1, 1));
}

t_frustum frustum_new_camera(t_mat4 view, t_mat4 proj) {

    t_frustum f = frustum_new_clipbox();
    f = frustum_transform(f, mat4_inverse(proj));
    f = frustum_transform(f, mat4_inverse(view));
    return f;

}

t_frustum frustum_slice(frustum f, float start, float end) {
    t_frustum r;
    r.ntr = vec3_add(f.ntr, vec3_mul(vec3_sub(f.ftr, f.ntr), start));
    r.ftr = vec3_add(f.ntr, vec3_mul(vec3_sub(f.ftr, f.ntr), end  ));

    r.ntl = vec3_add(f.ntl, vec3_mul(vec3_sub(f.ftl, f.ntl), start));
    r.ftl = vec3_add(f.ntl, vec3_mul(vec3_sub(f.ftl, f.ntl), end  ));

    r.nbr = vec3_add(f.nbr, vec3_mul(vec3_sub(f.fbr, f.nbr), start));
    r.fbr = vec3_add(f.nbr, vec3_mul(vec3_sub(f.fbr, f.nbr), end  ));

    r.nbl = vec3_add(f.nbl, vec3_mul(vec3_sub(f.fbl, f.nbl), start));
    r.fbl = vec3_add(f.nbl, vec3_mul(vec3_sub(f.fbl, f.nbl), end  ));
    return r;
}

t_vec3 frustum_center(t_frustum f) {
    t_vec3 total = vec3_zero();
    total = vec3_add(total, f.ntr);
    total = vec3_add(total, f.ftr);
    total = vec3_add(total, f.ntl);
    total = vec3_add(total, f.ftl);
    total = vec3_add(total, f.nbr);
    total = vec3_add(total, f.fbr);
    total = vec3_add(total, f.nbl);
    total = vec3_add(total, f.fbl);
    return vec3_div(total, 8);
}

t_vec3 frustum_maximums(t_frustum f) {
    t_vec3 r;
    r.x = max(max(max(max(max(max(max(f.ntr.x, f.ftr.x), f.ntl.x), f.ftl.x), f.nbr.x), f.fbr.x), f.nbl.x), f.fbl.x);
    r.y = max(max(max(max(max(max(max(f.ntr.y, f.ftr.y), f.ntl.y), f.ftl.y), f.nbr.y), f.fbr.y), f.nbl.y), f.fbl.y);
    r.z = max(max(max(max(max(max(max(f.ntr.z, f.ftr.z), f.ntl.z), f.ftl.z), f.nbr.z), f.fbr.z), f.nbl.z), f.fbl.z);
    return r;
}

t_vec3 frustum_minimums(t_frustum f) {
    t_vec3 r;
    r.x = min(min(min(min(min(min(min(f.ntr.x, f.ftr.x), f.ntl.x), f.ftl.x), f.nbr.x), f.fbr.x), f.nbl.x), f.fbl.x);
    r.y = min(min(min(min(min(min(min(f.ntr.y, f.ftr.y), f.ntl.y), f.ftl.y), f.nbr.y), f.fbr.y), f.nbl.y), f.fbl.y);
    r.z = min(min(min(min(min(min(min(f.ntr.z, f.ftr.z), f.ntl.z), f.ftl.z), f.nbr.z), f.fbr.z), f.nbl.z), f.fbl.z);
    return r;
}

t_frustum frustum_transform(t_frustum f, t_mat4 m) {
    t_frustum r;
    r.ntr = mat4_mul_vec3(m, f.ntr);
    r.ftr = mat4_mul_vec3(m, f.ftr);
    r.ntl = mat4_mul_vec3(m, f.ntl);
    r.ftl = mat4_mul_vec3(m, f.ftl);
    r.nbr = mat4_mul_vec3(m, f.nbr);
    r.fbr = mat4_mul_vec3(m, f.fbr);
    r.nbl = mat4_mul_vec3(m, f.nbl);
    r.fbl = mat4_mul_vec3(m, f.fbl);
    return r;
}

t_frustum frustum_translate(t_frustum f, t_vec3 v) {
    t_frustum r;
    r.ntr = vec3_add(f.ntr, v);
    r.ftr = vec3_add(f.ftr, v);
    r.ntl = vec3_add(f.ntl, v);
    r.ftl = vec3_add(f.ftl, v);
    r.nbr = vec3_add(f.nbr, v);
    r.fbr = vec3_add(f.fbr, v);
    r.nbl = vec3_add(f.nbl, v);
    r.fbl = vec3_add(f.fbl, v);
    return r;
}

t_box frustum_box(t_frustum f) {

    t_box b;
    b.top     = plane_new(f.ntr, vec3_normalize(vec3_cross(vec3_sub(f.ftr, f.ntr), vec3_sub(f.ntl, f.ntr))));
    b.bottom  = plane_new(f.nbr, vec3_normalize(vec3_cross(vec3_sub(f.nbl, f.nbr), vec3_sub(f.fbr, f.nbr))));
    b.left    = plane_new(f.ntl, vec3_normalize(vec3_cross(vec3_sub(f.ftl, f.ntl), vec3_sub(f.nbl, f.ntl))));
    b.right   = plane_new(f.ntr, vec3_normalize(vec3_cross(vec3_sub(f.nbr, f.ntr), vec3_sub(f.ftr, f.ntr))));
    b.front   = plane_new(f.ftr, vec3_normalize(vec3_cross(vec3_sub(f.ftl, f.ftr), vec3_sub(f.fbr, f.ftr))));
    b.back    = plane_new(f.ntr, vec3_normalize(vec3_cross(vec3_sub(f.nbr, f.ntr), vec3_sub(f.ntl, f.ntr))));
    return b;
}

bool frustum_outside_box(t_frustum f, t_box b) {
    error("Unimplemented");
    return false;
}

bool sphere_outside_frustum(t_sphere s, t_frustum f) {
    return sphere_outside_box(s, frustum_box(f));
}

bool sphere_inside_frustum(t_sphere s, t_frustum f) {
    return sphere_inside_box(s, frustum_box(f));
}

bool sphere_intersects_frustum(t_sphere s, t_frustum f) {
    return sphere_intersects_box(s, frustum_box(f));
}

bool sphere_outside_sphere(t_sphere s1, t_sphere s2) {
    float rtot = (s1.radius + s2.radius);
    return vec3_dist_sqrd(s1.center, s2.center) > rtot * rtot;
}

t_sphere sphere_unit() {
    return sphere_new(vec3_zero(), 1);
}

t_sphere sphere_point() {
    return sphere_new(vec3_zero(), 0);
}

t_sphere sphere_new(t_vec3 center, float radius) {
    t_sphere bs;
    bs.center = center;
    bs.radius = radius;
    return bs;
}

t_sphere sphere_of_box(t_box bb) {

    float x_max = bb.left.position.x;
    float x_min = bb.right.position.x;
    float y_max = bb.top.position.y;
    float y_min = bb.bottom.position.y;
    float z_max = bb.front.position.z;
    float z_min = bb.back.position.z;

    t_vec3 center;
    center.x = (x_min + x_max) / 2;
    center.y = (y_min + y_max) / 2;
    center.z = (z_min + z_max) / 2;

    float radius = 0;
    radius = max(radius, vec3_dist(center, vec3_new(x_min, y_min, z_min)));
    radius = max(radius, vec3_dist(center, vec3_new(x_max, y_min, z_min)));
    radius = max(radius, vec3_dist(center, vec3_new(x_min, y_max, z_min)));
    radius = max(radius, vec3_dist(center, vec3_new(x_min, y_min, z_max)));
    radius = max(radius, vec3_dist(center, vec3_new(x_min, y_max, z_max)));
    radius = max(radius, vec3_dist(center, vec3_new(x_max, y_max, z_min)));
    radius = max(radius, vec3_dist(center, vec3_new(x_max, y_min, z_max)));
    radius = max(radius, vec3_dist(center, vec3_new(x_max, y_max, z_max)));

    t_sphere bs;
    bs.center = center;
    bs.radius = radius;
    return bs;
}

t_sphere sphere_of_frustum(t_frustum f) {

    t_sphere s;
    s.center = frustum_center(f);
    s.radius = 0;
    s.radius = max(s.radius, vec3_dist(s.center, f.ntr));
    s.radius = max(s.radius, vec3_dist(s.center, f.ftr));
    s.radius = max(s.radius, vec3_dist(s.center, f.ntl));
    s.radius = max(s.radius, vec3_dist(s.center, f.ftl));
    s.radius = max(s.radius, vec3_dist(s.center, f.nbr));
    s.radius = max(s.radius, vec3_dist(s.center, f.fbr));
    s.radius = max(s.radius, vec3_dist(s.center, f.nbl));
    s.radius = max(s.radius, vec3_dist(s.center, f.fbl));

    return s;

}

t_sphere sphere_merge(t_sphere bs1, t_sphere bs2) {

    t_vec3 dir = vec3_sub(bs2.center, bs1.center);
    t_vec3 dirnorm = vec3_normalize(dir);

    t_vec3 p0 = vec3_sub(bs1.center, vec3_mul(dirnorm, bs1.radius));
    t_vec3 p1 = vec3_add(bs2.center, vec3_mul(dirnorm, bs2.radius));

    t_vec3 center = vec3_div(vec3_add(p0, p1), 2);
    float dist = vec3_dist(center, p0);

    return sphere_new(center, dist);
}

t_sphere sphere_merge_many(t_sphere* s, int count) {

    t_sphere ret = s[0];
    for (int i = 1; i < count; i++) {
        ret = sphere_merge(ret, s[i]);
    }

    return ret;
}

bool sphere_inside_box(t_sphere s, t_box b) {

    if (!sphere_inside_plane(s, b.front))  { return false; }
    if (!sphere_inside_plane(s, b.back))   { return false; }
    if (!sphere_inside_plane(s, b.top))    { return false; }
    if (!sphere_inside_plane(s, b.bottom)) { return false; }
    if (!sphere_inside_plane(s, b.left))   { return false; }
    if (!sphere_inside_plane(s, b.right))  { return false; }

    return true;

}

bool sphere_outside_box(t_sphere s, t_box b) {
    return !(sphere_inside_box(s, b) || sphere_intersects_box(s, b));
}

bool sphere_intersects_box(t_sphere s, t_box b) {

    bool in_left   = !sphere_outside_plane(s, b.left);
    bool in_right  = !sphere_outside_plane(s, b.right);
    bool in_front  = !sphere_outside_plane(s, b.front);
    bool in_back   = !sphere_outside_plane(s, b.back);
    bool in_top    = !sphere_outside_plane(s, b.top);
    bool in_bottom = !sphere_outside_plane(s, b.bottom);

    if (sphere_intersects_plane(s, b.top) &&
        in_left && in_right && in_front && in_back) {
        return true;
    }

    if (sphere_intersects_plane(s, b.bottom) &&
        in_left && in_right && in_front && in_back) {
        return true;
    }

    if (sphere_intersects_plane(s, b.left) &&
        in_top && in_bottom && in_front && in_back) {
        return true;
    }

    if (sphere_intersects_plane(s, b.right) &&
        in_top && in_bottom && in_front && in_back) {
        return true;
    }

    if (sphere_intersects_plane(s, b.front) &&
        in_top && in_bottom && in_left && in_right) {
        return true;
    }

    if (sphere_intersects_plane(s, b.back) &&
        in_top && in_bottom && in_left && in_right) {
        return true;
    }

    return false;

}

t_sphere sphere_transform(t_sphere s, t_mat4 world) {

    t_vec3 center = mat4_mul_vec3(world, s.center);
    float radius = s.radius * max(max(world.xx, world.yy), world.zz);

    return sphere_new(center, radius);
}

t_sphere sphere_translate(t_sphere s, t_vec3 x) {
    s.center = vec3_add(s.center, x);
    return s;
}

t_sphere sphere_scale(t_sphere s, float x) {
    s.radius *= x;
    return s;
}

t_sphere sphere_transform_space(t_sphere s, t_mat3 space) {

    t_vec3 center = mat3_mul_vec3(space, s.center);
    float radius = s.radius * max(max(space.xx, space.yy), space.zz);

    return sphere_new(center, radius);
}

bool point_inside_sphere(t_sphere s, t_vec3 point) {
    return vec3_dist(s.center, point) < s.radius;
}

bool point_outside_sphere(t_sphere s, t_vec3 point) {
    return vec3_dist(s.center, point) > s.radius;
}

bool point_intersects_sphere(t_sphere s, t_vec3 point) {
    return vec3_dist(s.center, point) == s.radius;
}

bool line_inside_sphere(t_sphere s, t_vec3 start, t_vec3 end) {
    return point_swept_inside_sphere(s, vec3_sub(end, start), start);
}

bool line_outside_sphere(t_sphere s, t_vec3 start, t_vec3 end) {
    return point_swept_outside_sphere(s, vec3_sub(end, start), start);
}

bool line_intersects_sphere(t_sphere s, t_vec3 start, t_vec3 end) {
    return point_swept_intersects_sphere(s, vec3_sub(end, start), start);
}

bool sphere_inside_plane(t_sphere s, t_plane p) {
    return -plane_distance(p, s.center) > s.radius;
}

bool sphere_outside_plane(t_sphere s, t_plane p) {
    return plane_distance(p, s.center) > s.radius;
}

bool sphere_intersects_plane(t_sphere s, t_plane p) {
    return fabs(plane_distance(p, s.center)) <= s.radius;
}

bool sphere_swept_inside_plane(t_sphere s, t_vec3 v, t_plane p) {

    float angle = vec3_dot(p.direction, v);
    float dist  = vec3_dot(p.direction, vec3_sub(s.center, p.position));

    if (-dist <= s.radius) { return false; }

    float t0 = ( s.radius - dist) / angle;
    float t1 = (-s.radius - dist) / angle;

    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));

}

bool sphere_swept_outside_plane(t_sphere s, t_vec3 v, t_plane p) {

    float angle = vec3_dot(p.direction, v);
    float dist  = vec3_dot(p.direction, vec3_sub(s.center, p.position));

    if ( dist <= s.radius ) { return false; }

    float t0 = ( s.radius - dist) / angle;
    float t1 = (-s.radius - dist) / angle;

    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));

}

bool sphere_swept_intersects_plane(t_sphere s, t_vec3 v, t_plane p) {

    float angle = vec3_dot(p.direction, v);
    float dist  = vec3_dot(p.direction, vec3_sub(s.center, p.position));

    if ( fabs(dist) <= s.radius ) { return true; }

    float t0 = ( s.radius - dist) / angle;
    float t1 = (-s.radius - dist) / angle;

    return (between_or(t0, 0, 1) || between_or(t1, 0, 1));

}

static bool quadratic(float a, float b, float c, float* t0, float* t1) {

    float descrim = b*b - 4*a*c;

    if (descrim < 0) {

        return false;

    } else {

        float d = sqrtf(descrim);
        float q = (b < 0) ? (-b - d) / 2.0 : (-b + d) / 2.0;

        *t0 = q / a;
        *t1 = c / q;

        return true;
    }

}

bool point_swept_inside_sphere(t_sphere s, t_vec3 v, t_vec3 point) {

    error("Unimplemented");
    return false;

}

bool point_swept_outside_sphere(t_sphere s, t_vec3 v, t_vec3 point) {

    float sdist = vec3_dist_sqrd(point, s.center);

    if (sdist <= s.radius * s.radius) { return false; }

    t_vec3  o = vec3_sub(point, s.center);
    float A = vec3_dot(v, v);
    float B = 2 * vec3_dot(v, o);
    float C = vec3_dot(o, o) - (s.radius * s.radius);

    float t0, t1, t;
    if (!quadratic(A, B, C, &t0, &t1)) { return true; }

    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));

}

bool point_swept_intersects_sphere(t_sphere s, t_vec3 v, t_vec3 point) {

    error("Unimplemented");
    return false;

}

bool sphere_swept_outside_sphere(t_sphere s1, t_vec3 v, t_sphere s2) {

    float sdist = vec3_dist_sqrd(s1.center, s2.center);
    float rtot = s1.radius + s2.radius;

    if (sdist <= rtot * rtot) { return false; }

    t_vec3  o = vec3_sub(s1.center, s2.center);
    float A = vec3_dot(v, v);
    float B = 2 * vec3_dot(v, o);
    float C = vec3_dot(o, o) - (rtot * rtot);

    float t0, t1, t;
    if (!quadratic(A, B, C, &t0, &t1)) { return true; }

    return (!between_or(t0, 0, 1) && !between_or(t1, 0, 1));

}

bool sphere_swept_inside_sphere(t_sphere s1, t_vec3 v, t_sphere s2) {

    error("Unimplemented");
    return false;

}

bool sphere_swept_intersects_sphere(t_sphere s1, t_vec3 v, t_sphere s2) {

    error("Unimplemented");
    return false;

}

bool point_inside_triangle(vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2) {

    t_vec3 d0 = vec3_sub(v2, v0);
    t_vec3 d1 = vec3_sub(v1, v0);
    t_vec3 d2 = vec3_sub(p, v0);

    float dot00 = vec3_dot(d0, d0);
    float dot01 = vec3_dot(d0, d1);
    float dot02 = vec3_dot(d0, d2);
    float dot11 = vec3_dot(d1, d1);
    float dot12 = vec3_dot(d1, d2);

    float inv_dom = 1.0f / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * inv_dom;
    float v = (dot00 * dot12 - dot01 * dot02) * inv_dom;

    return (u >= 0) && (v >= 0) && (u + v < 1);

}

bool sphere_intersects_face(t_sphere s, t_vec3 v0, t_vec3 v1, t_vec3 v2, t_vec3 norm) {

    if (!sphere_intersects_plane(s, plane_new(v0, norm))) { return false; }

    t_vec3 c = plane_closest(plane_new(v0, norm), s.center);

    return point_inside_triangle(c, v0, v1, v2);

}

t_ellipsoid ellipsoid_new(vec3 center, t_vec3 radiuses) {
    ellipsoid e;
    e.center = center;
    e.radiuses = radiuses;
    return e;
}

t_ellipsoid ellipsoid_of_sphere(t_sphere s) {
    t_vec3 radiuses = vec3_new(s.radius, s.radius, s.radius);
    return ellipsoid_new(s.center, radiuses);
}

t_ellipsoid ellipsoid_transform(ellipsoid e, t_mat4 m) {
    e.center = mat4_mul_vec3(m, e.center);
    e.radiuses = mat3_mul_vec3(mat4_to_mat3(m), e.radiuses);
    return e;
}

t_mat3 ellipsoid_space(t_ellipsoid e) {

    return mat3_new(
            1.0/e.radiuses.x, 0, 0,
            0, 1.0/e.radiuses.y, 0,
            0, 0, 1.0/e.radiuses.z);

}

t_mat3 ellipsoid_inv_space(t_ellipsoid e) {

    return mat3_new(
            e.radiuses.x, 0, 0,
            0, e.radiuses.y, 0,
            0, 0, e.radiuses.z);

}

t_capsule capsule_new(vec3 start, t_vec3 end, float radius) {
    capsule c;
    c.start = start;
    c.end = end;
    c.radius = radius;
    return c;
}

t_capsule capsule_transform(t_capsule c, t_mat4 m) {
    c.start  = mat4_mul_vec3(m, c.start);
    c.end    = mat4_mul_vec3(m, c.end);
    c.radius = c.radius * max(max(m.xx, m.yy), m.zz);
    return c;
}

bool capsule_inside_plane(t_capsule c, t_plane p) {
    return (sphere_inside_plane(sphere_new(c.start, c.radius), p) &&
            sphere_inside_plane(sphere_new(c.end,   c.radius), p));
}

bool capsule_outside_plane(t_capsule c, t_plane p) {
    return (sphere_outside_plane(sphere_new(c.start, c.radius), p) &&
            sphere_outside_plane(sphere_new(c.end,   c.radius), p));
}

bool capsule_intersects_plane(t_capsule c, t_plane p) {
    return (!capsule_inside_plane(c, p) && !capsule_outside_plane(c, p));
}

vertex vertex_new() {
    t_vertex v;
    memset(&v, 0, sizeof(t_vertex));
    return v;
}

bool vertex_equal(t_vertex v1, t_vertex v2) {

    if(!vec3_equ(v1.position, v2.position)) { return false; }
    if(!vec3_equ(v1.normal, v2.normal)) { return false; }
    if(!vec2_equ(v1.uvs, v2.uvs)) { return false; }

    return true;
}

void vertex_print(t_vertex v) {

    printf("V(Position: "); vec3_print(v.position);
    printf(", Normal: "); vec3_print(v.normal);
    printf(", Tangent: "); vec3_print(v.tangent);
    printf(", Binormal: "); vec3_print(v.binormal);
    printf(", Color: "); vec4_print(v.color);
    printf(", Uvs: "); vec2_print(v.uvs);
    printf(")");

}

void mesh_print(t_mesh* m) {
    printf("Num Verts: %i\n", m->num_verts);
    printf("Num Tris: %i\n", m->num_triangles);
    for(int i=0; i < m->num_verts; i++) {
        vertex_print(m->verticies[i]); printf("\n");
    }
    printf("Triangle Indicies:");
    for(int i=0; i < m->num_triangles * 3; i++) {
        printf("%i ", m->triangles[i]);
    }
    printf("\n");
}

t_mesh* mesh_new() {

    t_mesh* m = malloc(sizeof(mesh));
    m->num_verts = 0;
    m->num_triangles = 0;
    m->verticies = malloc(sizeof(t_vertex) * m->num_verts);
    m->triangles = malloc(sizeof(int) * m->num_triangles * 3);

    return m;

}

void mesh_delete(t_mesh* m) {
    free(m->verticies);
    free(m->triangles);
    free(m);
}

void mesh_generate_tangents(t_mesh* m) {

    /* Clear all tangents to 0,0,0 */
    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].tangent = vec3_zero();
        m->verticies[i].binormal = vec3_zero();
    }

    /* Loop over faces, calculate tangent and append to verticies of that face */
    int i = 0;
    while( i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        t_vertex v1 = m->verticies[t_i1];
        t_vertex v2 = m->verticies[t_i2];
        t_vertex v3 = m->verticies[t_i3];

        t_vec3 face_tangent = triangle_tangent(v1, v2, v3);
        t_vec3 face_binormal = triangle_binormal(v1, v2, v3);

        v1.tangent = vec3_add(face_tangent, v1.tangent);
        v2.tangent = vec3_add(face_tangent, v2.tangent);
        v3.tangent = vec3_add(face_tangent, v3.tangent);

        v1.binormal = vec3_add(face_binormal, v1.binormal);
        v2.binormal = vec3_add(face_binormal, v2.binormal);
        v3.binormal = vec3_add(face_binormal, v3.binormal);

        m->verticies[t_i1] = v1;
        m->verticies[t_i2] = v2;
        m->verticies[t_i3] = v3;

        i = i + 3;
    }

    /* normalize all tangents */
    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].tangent = vec3_normalize( m->verticies[i].tangent );
        m->verticies[i].binormal = vec3_normalize( m->verticies[i].binormal );
    }

}

void mesh_generate_normals(t_mesh* m) {

    /* Clear all normals to 0,0,0 */
    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].normal = vec3_zero();
    }

    /* Loop over faces, calculate normals and append to verticies of that face */
    int i = 0;
    while( i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        t_vertex v1 = m->verticies[t_i1];
        t_vertex v2 = m->verticies[t_i2];
        t_vertex v3 = m->verticies[t_i3];

        t_vec3 face_normal = triangle_normal(v1, v2, v3);

        v1.normal = vec3_add(face_normal, v1.normal);
        v2.normal = vec3_add(face_normal, v2.normal);
        v3.normal = vec3_add(face_normal, v3.normal);

        m->verticies[t_i1] = v1;
        m->verticies[t_i2] = v2;
        m->verticies[t_i3] = v3;

        i = i + 3;
    }

    /* normalize all normals */
    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].normal = vec3_normalize( m->verticies[i].normal );
    }

}

void mesh_generate_orthagonal_tangents(t_mesh* m) {

    /* Clear all tangents to 0,0,0 */
    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].tangent = vec3_zero();
        m->verticies[i].binormal = vec3_zero();
    }

    /* Loop over faces, calculate tangent and append to verticies of that face */
    int i = 0;
    while( i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        t_vertex v1 = m->verticies[t_i1];
        t_vertex v2 = m->verticies[t_i2];
        t_vertex v3 = m->verticies[t_i3];

        t_vec3 face_normal = triangle_normal(v1, v2, v3);
        t_vec3 face_binormal_temp = triangle_binormal(v1, v2, v3);

        t_vec3 face_tangent = vec3_normalize( vec3_cross(face_binormal_temp, face_normal) );
        t_vec3 face_binormal = vec3_normalize( vec3_cross(face_tangent, face_normal) );

        v1.tangent = vec3_add(face_tangent, v1.tangent);
        v2.tangent = vec3_add(face_tangent, v2.tangent);
        v3.tangent = vec3_add(face_tangent, v3.tangent);

        v1.binormal = vec3_add(face_binormal, v1.binormal);
        v2.binormal = vec3_add(face_binormal, v2.binormal);
        v3.binormal = vec3_add(face_binormal, v3.binormal);

        m->verticies[t_i1] = v1;
        m->verticies[t_i2] = v2;
        m->verticies[t_i3] = v3;

        i = i + 3;
    }

    /* normalize all tangents */
    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].tangent = vec3_normalize( m->verticies[i].tangent );
        m->verticies[i].binormal = vec3_normalize( m->verticies[i].binormal );
    }
}

void mesh_generate_texcoords_cylinder(t_mesh* m) {

    t_vec3 unwrap_vector = vec2_new(1, 0);

    float max_height = -99999999;
    float min_height = 99999999;

    for(int i = 0; i < m->num_verts; i++) {
        float v = m->verticies[i].position.y;
        max_height = max(max_height, v);
        min_height = min(min_height, v);

        t_vec3 proj_position = vec2_new(m->verticies[i].position.x, m->verticies[i].position.z);
        t_vec3 from_center = vec2_normalize(proj_position);
        float u = (vec2_dot(from_center, unwrap_vector) + 1) / 8;

        m->verticies[i].uvs = vec2_new(u, v);
    }

    float scale = (max_height - min_height);

    for(int i = 0; i < m->num_verts; i++) {
        m->verticies[i].uvs = vec2_new(m->verticies[i].uvs.x, m->verticies[i].uvs.y / scale);
    }

}

float mesh_surface_area(t_mesh* m) {

    float total = 0.0;

    int i = 0;
    while( i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        t_vertex v1 = m->verticies[t_i1];
        t_vertex v2 = m->verticies[t_i2];
        t_vertex v3 = m->verticies[t_i3];

        total += triangle_area(v1, v2, v3);

        i = i + 3;
    }

    return total;

}

void mesh_translate(t_mesh* m, t_vec3 translation) {

    int i = 0;
    while(i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        m->verticies[t_i1].position = vec3_add(m->verticies[t_i1].position, translation);
        m->verticies[t_i2].position = vec3_add(m->verticies[t_i2].position, translation);
        m->verticies[t_i3].position = vec3_add(m->verticies[t_i3].position, translation);

        i = i + 3;
    }

}

void mesh_scale(t_mesh* m, float scale) {

    int i = 0;
    while(i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        m->verticies[t_i1].position = vec3_mul(m->verticies[t_i1].position, scale);
        m->verticies[t_i2].position = vec3_mul(m->verticies[t_i2].position, scale);
        m->verticies[t_i3].position = vec3_mul(m->verticies[t_i3].position, scale);

        i = i + 3;
    }

}

void mesh_transform(t_mesh* m, t_mat4 transform) {

    int i = 0;
    while(i < m->num_triangles * 3) {

        int t_i1 = m->triangles[i];
        int t_i2 = m->triangles[i+1];
        int t_i3 = m->triangles[i+2];

        m->verticies[t_i1].position = mat4_mul_vec3(transform, m->verticies[t_i1].position);
        m->verticies[t_i2].position = mat4_mul_vec3(transform, m->verticies[t_i2].position);
        m->verticies[t_i3].position = mat4_mul_vec3(transform, m->verticies[t_i3].position);

        i = i + 3;
    }

}

t_sphere mesh_bounding_sphere(t_mesh* m) {

    t_sphere s = sphere_new(vec3_zero(), 0);

    for (int i = 0; i < m->num_verts; i++) {
        s.center = vec3_add(s.center, m->verticies[i].position);
    }
    s.center = vec3_div(s.center, m->num_verts);

    for (int i = 0; i < m->num_verts; i++) {
        s.radius = max(s.radius, vec3_dist(s.center, m->verticies[i].position));
    }

    return s;
}

void model_print(t_model *m) {
    for(int i=0; i<m->num_meshes; i++) {
        mesh_print( m->meshes[i] );
    }
}

t_model* model_new() {
    t_model* m = malloc(sizeof(t_model));
    m->num_meshes = 0;
    m->meshes = malloc(sizeof(t_mesh*) * m->num_meshes);
    return m;
}

void model_delete(t_model *m) {
    for(int i=0; i<m->num_meshes; i++) {
        mesh_delete( m->meshes[i] );
    }
    free(m);
}

void model_generate_normals(t_model *m) {

    for(int i = 0; i < m->num_meshes; i++) {
        mesh_generate_normals( m->meshes[i] );
    }

}

void model_generate_tangents(t_model *m) {

    for(int i = 0; i < m->num_meshes; i++) {
        mesh_generate_tangents( m->meshes[i] );
    }

}

void model_generate_orthagonal_tangents(t_model *m) {
    for(int i = 0; i < m->num_meshes; i++) {
        mesh_generate_orthagonal_tangents( m->meshes[i] );
    }
}

void model_generate_texcoords_cylinder(t_model *m) {
    for(int i = 0; i < m->num_meshes; i++) {
        mesh_generate_texcoords_cylinder( m->meshes[i] );
    }
}

float model_surface_area(t_model *m) {
    float total = 0.0f;

    for(int i = 0; i < m->num_meshes; i++) {
        total += mesh_surface_area( m->meshes[i] );
    }

    return total;
}

void model_translate(t_model *m, t_vec3 translation) {
    for(int i = 0; i < m->num_meshes; i++) {
        mesh_translate(m->meshes[i], translation);
    }
}

void model_scale(t_model *m, float scale) {
    for(int i = 0; i < m->num_meshes; i++) {
        mesh_scale(m->meshes[i], scale);
    }
}

void model_transform(t_model *m, t_mat4 transform) {
    for(int i = 0; i < m->num_meshes; i++) {
        mesh_transform(m->meshes[i], transform);
    }
}

t_vec3 triangle_tangent(t_vertex vert1, t_vertex vert2, t_vertex vert3) {

    t_vec3 pos1 = vert1.position;
    t_vec3 pos2 = vert2.position;
    t_vec3 pos3 = vert3.position;

    t_vec3 uv1 = vert1.uvs;
    t_vec3 uv2 = vert2.uvs;
    t_vec3 uv3 = vert3.uvs;

    /* Get component vectors */
    float x1 = pos2.x - pos1.x;
    float x2 = pos3.x - pos1.x;

    float y1 = pos2.y - pos1.y;
    float y2 = pos3.y - pos1.y;

    float z1 = pos2.z - pos1.z;
    float z2 = pos3.z - pos1.z;

    /* Generate uv space vectors */
    float s1 = uv2.x - uv1.x;
    float s2 = uv3.x - uv1.x;

    float t1 = uv2.y - uv1.y;
    float t2 = uv3.y - uv1.y;

    float r = 1.0f / ((s1 * t2) - (s2 * t1));

    t_vec3 tdir = vec3_new(
            (s1 * x2 - s2 * x1) * r,
            (s1 * y2 - s2 * y1) * r,
            (s1 * z2 - s2 * z1) * r);

    return vec3_normalize(tdir);

}

t_vec3 triangle_binormal(t_vertex vert1, t_vertex vert2, t_vertex vert3) {

    t_vec3 pos1 = vert1.position;
    t_vec3 pos2 = vert2.position;
    t_vec3 pos3 = vert3.position;

    t_vec3 uv1 = vert1.uvs;
    t_vec3 uv2 = vert2.uvs;
    t_vec3 uv3 = vert3.uvs;

    /* Get component Vectors */
    float x1 = pos2.x - pos1.x;
    float x2 = pos3.x - pos1.x;

    float y1 = pos2.y - pos1.y;
    float y2 = pos3.y - pos1.y;

    float z1 = pos2.z - pos1.z;
    float z2 = pos3.z - pos1.z;

    /* Generate uv space vectors */
    float s1 = uv2.x - uv1.x;
    float s2 = uv3.x - uv1.x;

    float t1 = uv2.y - uv1.y;
    float t2 = uv3.y - uv1.y;

    float r = 1.0f / ((s1 * t2) - (s2 * t1));

    t_vec3 sdir = vec3_new(
            (t2 * x1 - t1 * x2) * r,
            (t2 * y1 - t1 * y2) * r,
            (t2 * z1 - t1 * z2) * r
    );

    return vec3_normalize(sdir);

}

t_vec3 triangle_normal(t_vertex v1, t_vertex v2, t_vertex v3) {
    t_vec3 edge1 = vec3_sub(v2.position, v1.position);
    t_vec3 edge2 = vec3_sub(v3.position, v1.position);
    t_vec3 normal = vec3_cross(edge1, edge2);

    return vec3_normalize(normal);
}

float triangle_area(t_vertex v1, t_vertex v2, t_vertex v3) {

    t_vec3 ab = vec3_sub(v1.position, v2.position);
    t_vec3 ac = vec3_sub(v1.position, v3.position);

    float area = 0.5 * vec3_length(vec3_cross(ab, ac));

    return area;
}

t_vec3 triangle_random_position(t_vertex v1, t_vertex v2, t_vertex v3) {

    float r1 = (float)rand() / (float)RAND_MAX;
    float r2 = (float)rand() / (float)RAND_MAX;

    if(r1 + r2 >= 1) {
        r1 = 1 - r1;
        r2 = 1 - r2;
    }

    t_vec3 ab = vec3_sub(v1.position, v2.position);
    t_vec3 ac = vec3_sub(v1.position, v3.position);

    t_vec3 a = v1.position;
    a = vec3_sub(a, vec3_mul(ab , r1) );
    a = vec3_sub(a, vec3_mul(ac , r2) );

    return a;

}

t_vertex triangle_random_position_interpolation(t_vertex v1, t_vertex v2, t_vertex v3) {

    float r1 = (float)rand() / (float)RAND_MAX;
    float r2 = (float)rand() / (float)RAND_MAX;

    if(r1 + r2 >= 1) {
        r1 = 1 - r1;
        r2 = 1 - r2;
    }

    t_vertex v;

    t_vec3 v_pos, v_norm, v_tang, v_binorm;
    t_vec3 v_col;
    t_vec3 v_uv;

    v_pos = v1.position;
    v_pos = vec3_sub(v_pos, vec3_mul(vec3_sub(v1.position, v2.position) , r1) );
    v_pos = vec3_sub(v_pos, vec3_mul(vec3_sub(v1.position, v3.position) , r2) );

    v_norm = v1.normal;
    v_norm = vec3_sub(v_norm, vec3_mul(vec3_sub(v1.normal, v2.normal) , r1) );
    v_norm = vec3_sub(v_norm, vec3_mul(vec3_sub(v1.normal, v3.normal) , r2) );

    v_tang = v1.tangent;
    v_tang = vec3_sub(v_tang, vec3_mul(vec3_sub(v1.tangent, v2.tangent) , r1) );
    v_tang = vec3_sub(v_tang, vec3_mul(vec3_sub(v1.tangent, v3.tangent) , r2) );

    v_binorm = v1.binormal;
    v_binorm = vec3_sub(v_binorm, vec3_mul(vec3_sub(v1.binormal, v2.binormal) , r1) );
    v_binorm = vec3_sub(v_binorm, vec3_mul(vec3_sub(v1.binormal, v3.binormal) , r2) );

    v_col = v1.color;
    v_col = vec4_sub(v_col, vec4_mul(vec4_sub(v1.color, v2.color) , r1) );
    v_col = vec4_sub(v_col, vec4_mul(vec4_sub(v1.color, v3.color)  , r2) );

    v_uv = v1.uvs;
    v_uv = vec2_sub(v_uv, vec2_mul(vec2_sub(v1.uvs, v2.uvs) , r1) );
    v_uv = vec2_sub(v_uv, vec2_mul(vec2_sub(v1.uvs, v3.uvs)  , r2) );

    v.position = v_pos;
    v.normal = v_norm;
    v.tangent = v_tang;
    v.binormal = v_binorm;
    v.color = v_col;
    v.uvs = v_uv;

    return v;
}


float triangle_difference_u(t_vertex v1, t_vertex v2, t_vertex v3) {
    float max = v1.uvs.x;
    max = v2.uvs.x > max ? v2.uvs.x : max;
    max = v3.uvs.x > max ? v3.uvs.x : max;

    float min = v1.uvs.x;
    min = v2.uvs.x < min ? v2.uvs.x : min;
    min = v3.uvs.x < min ? v3.uvs.x : min;

    return max - min;
}

float triangle_difference_v(t_vertex v1, t_vertex v2, t_vertex v3) {
    float max = v1.uvs.y;
    max = v2.uvs.x > max ? v2.uvs.y : max;
    max = v3.uvs.x > max ? v3.uvs.y : max;

    float min = v1.uvs.y;
    min = v2.uvs.y < min ? v2.uvs.y : min;
    min = v3.uvs.y < min ? v3.uvs.y : min;

    return max - min;
}

