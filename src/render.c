/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchett <mchett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:23:55 by mchett            #+#    #+#             */
/*   Updated: 2019/10/02 15:55:10 by mchett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int     cast_ray(t_vect *orig, t_vect *dir, t_sphere *sphere)
{
    if (ray_intersect(orig, dir, sphere) == 0)
        return (255);//(new_vect2(0.2, 0.7, 0.8)); // background color
    return (16777215);//(new_vect2(0.4, 0.4, 0.3));
}

void    render(t_sphere *sphere, t_image *img) 
{
	const float fov = M_PI/3.;

    for (size_t j = 0; j<W_H; j++) {
        for (size_t i = 0; i<W_W; i++) {
            float x =  (2*(i + 0.5)/(double)W_W  - 1)*tan(fov/2.)*W_W/(double)W_H;
            float y = -(2*(j + 0.5)/(double)W_H - 1)*tan(fov/2.);
            t_vect *dir = new_vect2(x, y, -1);
			vect_norm(dir);
			image_set_pixel(img, i, j, cast_ray(new_vect2(0,0,0), dir, sphere));
            //framebuffer[i+j*W_W] = cast_ray(new_vect2(0,0,0), dir, sphere);
        }
    }

}