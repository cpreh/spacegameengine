#version 120

$$$HEADER$$$

varying vec2 varying_texcoord;
varying vec3 varying_normal;
varying vec3 varying_vertex_to_light_vector;

void 
main()
{
	const vec4 
		ambient_color = 
			vec4(0.1, 0.0, 0.0, 1.0),
		diffuse_color = 
			vec4(1.0, 0.0, 0.0, 1.0);

	float diffuse_term = 
		clamp(
			dot(
				varying_normal + 
				vec3(
					texture2D(
						normal_texture,
						varying_texcoord)), 
				normalize(
					varying_vertex_to_light_vector)), 
			0.0, 
			1.0);

	// Calculating The Final Color
	gl_FragColor = 
		ambient_color + diffuse_color * diffuse_term;
}
