#include "mrt_parse.h"
#include "print/mrt_print.h"
#include "trace/mrt_trace.h"

static int	parse_disc_obj(t_scene *scene, char **split, int line_num);

int	parse_light_disc(t_scene *scene, char **split, int line_num)
{
	t_list	*light;
	t_light	*c_light;

	if (ft_split_count_str(split) != 7)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	light = light_new();
	if (light == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_light), light);
	c_light = light_cont(light);
	if (parse_disc_obj(scene, split, line_num))
		return (-1);
	if (double_from_str(split[6], 4, 2, &(c_light->weight))
		|| c_light->weight < 0.0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_LW, NULL));
	c_light->linked_c_obj = ft_lstlast(scene->l_obj)->content;
	c_light->print = &print_light_disc;
	c_light->pdf_value = &pdf_disc;
	c_light->random_dir = &random_dir_to_disc;
	return (0);
}

static int	parse_disc_obj(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_obj	*c_obj;

	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	c_obj = obj_cont(obj);
	if (parse_vec3(split[1], &(c_obj->di.pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(c_obj->di.dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	if (double_from_str(split[3], 6, 3, &(c_obj->di.radius)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RAD, NULL));
	if (parse_color(split[4], &(c_obj->material.color)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_COLOR, NULL));
	c_obj->material.surface[SURF_EMISSION] = 1.0;
	if (double_from_str(split[5], 4, 2, &(c_obj->material.brightness)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_BRIGHT, NULL));
	c_obj->print = &print_obj_disc;
	c_obj->intersec = &intersec_disc;
	c_obj->normal = &normal_disc;
	c_obj->material.get_color = &obj_color;
	return (0);
}
