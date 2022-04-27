# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 09:02:38 by tjensen           #+#    #+#              #
#    Updated: 2022/04/27 12:56:56 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= miniRT

CC				:= cc
CFLAGS			:= -Wall -Wextra -pthread -O3 #-Werror

SRCS			:= main.c mrt_color.c mrt_obj.c mrt_scene.c mrt_is.c
SRCS_GRAPHIC	:= mrt_graphic_render.c
SRCS_MATH		:= mrt_math_color.c mrt_math_vec3_1.c mrt_math_vec3_2.c
SRCS_PARSE		:= mrt_parse_cam.c mrt_parse_material.c mrt_parse_obj_sphere.c mrt_parse_scene.c \
				   mrt_parse_amb.c mrt_parse_color.c mrt_parse_obj_cylinder.c mrt_parse_ppm.c mrt_parse_utils.c \
				   mrt_parse_bg.c mrt_parse_img.c mrt_parse_is.c mrt_parse_obj_plane.c mrt_parse_sampling.c mrt_parse_vec3.c
SRCS_PRINT		:= mrt_print_error.c mrt_print_is.c mrt_print_obj_plane.c mrt_print_scene.c \
				   mrt_print_color.c mrt_print_obj_cylinder.c mrt_print_obj_sphere.c mrt_print_vec3.c mrt_print_material.c
SRCS_TRACE		:= mrt_trace_dielectric.c mrt_trace_diffuse.c mrt_trace_onb.c mrt_trace_specular.c \
				   mrt_trace.c mrt_trace_random.c mrt_trace_obj_normal.c mrt_trace_obj_intersec.c mrt_trace_obj_random.c mrt_trace_obj_pdf.c

SRCS			+= $(addprefix graphic/, $(SRCS_GRAPHIC)) \
				   $(addprefix math/, $(SRCS_MATH)) \
				   $(addprefix parse/, $(SRCS_PARSE)) \
				   $(addprefix print/, $(SRCS_PRINT)) \
				   $(addprefix trace/, $(SRCS_TRACE))

SDIR			:= src
ODIR			:= obj
OBJS			:= $(addprefix $(ODIR)/, $(SRCS:.c=.o))
IDIR			:= $(SDIR)

LIBS			:= lib/libft/libft.a lib/libmlx/libmlx42.a
LDFLAGS			:= $(LIBS) -lm -lglfw -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS			+= -I. -I$(IDIR)

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

$(NAME): $(LIBS) $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(IDIR)/*.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

lib/libft/libft.a:
	make -C lib/libft/

lib/libmlx/libmlx42.a:
	make -C lib/libmlx/

all: $(NAME)

clean:
	make -C lib/libft fclean
	make -C lib/libmlx fclean
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) -r *.dSYM $(SDIR)/*.dSYM
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all
