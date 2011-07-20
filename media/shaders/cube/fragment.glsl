#version 120

$$$HEADER$$$

varying vec2 varying_texcoord;
varying vec3 varying_vertex_position;
varying vec3 varying_light_position;

void 
main()
{
	vec3 normal_coord = 
		vec3(0.0,0.0,1.0);

	if (enabled == 1)
		normal_coord = 
			normalize(
			vec3(
				texture2D(
					normal_texture,
					varying_texcoord)));

	vec3 eye_to_pos =
		normalize(
			camera - varying_vertex_position);

	vec3 pos_to_light = 
		normalize(
			varying_vertex_position - varying_light_position);

	float angle = 
		clamp(
			dot(
				normalize(
					normal_coord), 
				pos_to_light
				),
			0.0,
			1.0);

	float diffuse_term = 
		angle;

	float spec_exponent = 50;
	float spec_factor = 1.0;

	float specular_term =
		min(1.0,
		spec_factor *
			pow(max(0.0, dot(reflect(eye_to_pos, normal_coord), pos_to_light)), spec_exponent));

	// Calculating The Final Color
	gl_FragColor = 
		texture2D(
			color_texture,
			varying_texcoord)
			* max(0.02,diffuse_term)
		+ specular_term;
}
