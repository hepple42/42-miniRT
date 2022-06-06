#include "mrt_parse.h"
#include "print/mrt_print.h"

int	parse_obj_tube(t_scene *scene, char **split, int line_num)
{
	t_list	*obj;
	t_tube	*tb;

	if (ft_split_count_str(split) != 9)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_NUM, NULL));
	obj = obj_new(0);
	if (obj == NULL)
		return (print_error_scene(line_num, ERR_PARSE, strerror(errno), NULL));
	ft_lstadd_back(&(scene->l_obj), obj);
	tb = &(obj_cont(obj)->tb);
	if (parse_vec3(split[1], &(tb->pos)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_POS, NULL));
	if (parse_vec3(split[2], &(tb->dir)))
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_DIR, NULL));
	tb->dir = vec3_normalize(tb->dir);
	if (double_from_str(split[3], 6, 3, &(tb->radius)) || tb->radius <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_RAD, NULL));
	if (double_from_str(split[4], 6, 3, &(tb->height)) || tb->height <= 0)
		return (print_error_scene(line_num, ERR_PARSE, ERR_INVAL_HEIGHT, NULL));
	if (parse_material(&(obj_cont(obj)->material), &split[5], line_num))
		return (-1);
	obj_cont(obj)->print = &print_obj_tube;
	obj_cont(obj)->intersec = &intersec_tube;
	obj_cont(obj)->normal = &normal_tube;
	return (0);
}
