#include "mrt_trace.h"

t_vec3	specular(t_list *obj, t_ray *ray, t_hit *hit)
{
	t_vec3	dir;

	if (obj_cont(obj)->material.fuzz == 0.0)
		return (vec3_normalize(
				vec3_add(ray->dir,
					vec3_scale(-2.0
						* vec3_scalar_product(ray->dir, hit->normal),
						hit->normal))));
	dir = vec3_add(ray->dir, vec3_add(
				vec3_scale(-2.0 * vec3_scalar_product(ray->dir, hit->normal),
					hit->normal),
				vec3_scale(obj_material(obj)->fuzz, random_in_unit_sphere())));
	if (hit->side == OUTSIDE && vec3_scalar_product(dir, hit->normal) <= 0.0)
		return ((t_vec3){0.0, 0.0, 0.0});
	else if (hit->side == INSIDE
		&& vec3_scalar_product(dir, hit->normal) >= 0.0)
		return ((t_vec3){0.0, 0.0, 0.0});
	return (vec3_normalize(dir));
}
