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
		normal_coord += 
			vec3(
				texture2D(
					normal_texture,
					varying_texcoord));

	float diffuse_term = 
		clamp(
			dot(
				normalize(
					normal_coord), 
				normalize(
					varying_light_position - varying_vertex_position)), 
			0.0, 
			1.0);

	// Calculating The Final Color
	gl_FragColor = 
		texture2D(
			color_texture,
			varying_texcoord) * max(0.02,diffuse_term);
}
