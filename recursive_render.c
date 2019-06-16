#include "inc/rt.h"

# define AIR_DENSITY 1.0
# define HARDCODED_IOR	1.1

t_rgb	refract(t_render_data *data, t_shading shading, t_ray ray, int depth, float n)
{
	float	cosi;
	float	sint2;
	float	cost;
	t_ray	refracted_ray;

	cosi = -(dot(shading.normal, ray.dir));
	sint2 = n * n * (1.0 - cosi * cosi);
	if (sint2 > 1.0)
		return(new_rgb(0 ,0 ,0));
	cost = sqrt(1.0 - sint2);
	refracted_ray.dir = normalize(add(mult(ray.dir, n), mult(shading.normal, (n * cosi - cost))));
	refracted_ray.pos = substract(shading.hit, mult(shading.normal, EPSILON));
	return (trace_ray(data, refracted_ray, depth - 1));
}

t_rgb	reflect(t_render_data *data, t_shading shading, t_ray ray, int depth)
{
	float	cosi;
    t_ray   reflected_ray;

	cosi = -(dot(shading.normal, ray.dir));
    reflected_ray.pos = add(shading.hit, mult(shading.normal, EPSILON)); //EPSILON FOR MOVING A LITTLE AWAY FROM THE POINT TO OVERCOME FLOAT APPROXIMATION
    reflected_ray.dir = normalize(add(ray.dir, mult(shading.normal, cosi * 2)));
	return (trace_ray(data, reflected_ray, depth - 1));
}

float calculate_fresnel(t_v3f dir, t_shading shading) 
{ 
	float kr;
	float etai = AIR_DENSITY, etat = HARDCODED_IOR; 
	float cosi = dot(dir, (shading.normal)); 
	if (shading.is_inside)
		ft_swap(&etai, &etat);
  float sint = etai / etat * sqrtf(MAX(0.f, 1 - cosi * cosi)); 
    if (sint >= 1) {
        kr = 1;
    } 
    else { 
      float cost = sqrtf(MAX(0.f, 1 - sint * sint)); 
       cosi = fabs(cosi); 
      float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
      float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    }
    return (kr);
} 

// t_shading:
// 
// 	t_rgb		color - MATERIAL COLOR
// 	t_v3f		hit -  INTERSTACTION POINT
// 	t_v3f		normal - SURFACE NORMAL TO hit
// 	float		kd - MATERIAL DIFFUCE % 
// 	float		ka - MATERIAL AMBIENT %
// 	float		ks - MATERIAL SPECULAR %
// 	float		gs - SHINE EFFECT SIZE
// 	float		is_reflective;
// 

t_rgb trace_new_ray(t_render_data *data, t_ray ray, t_shading shading, int depth)
{
	t_rgb	refl_color;
	t_rgb   refr_color;
	t_rgb   color;
	float	fr;

	refl_color = reflect(data, shading, ray, depth);
	if (!shading.krefract)
		return (refl_color);

	refr_color = refract(data, shading, ray, depth, AIR_DENSITY / HARDCODED_IOR); // HARDCODED
	fr = calculate_fresnel(ray.dir, shading);
	color.red = refl_color.red * fr + refr_color.red * (1.0f - fr);
	color.green = refl_color.green * fr + refr_color.green * (1.0f - fr);
	color.blue = refl_color.blue * fr + refr_color.blue * (1.0f - fr);
	// color = color_interpolate(refl_color, refr_color, 0.5);

	return (color_mult(color, 1));
}