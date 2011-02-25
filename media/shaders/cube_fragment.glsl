#version 120

$$$HEADER$$$

varying vec2 varying_texcoord;
varying vec3 varying_vertex_position;
varying vec3 varying_light_position;

void 
main()
{
	const vec4 
		ambient_color = 
			vec4(0.1, 0.1, 0.1, 1.0),
		diffuse_color = 
			vec4(1.0, 0.5, 0.5, 1.0);

	float diffuse_term = 
		clamp(
			dot(
				normalize(
					vec3(0.0,0.0,1.0) + 
					vec3(
						texture2D(
							normal_texture,
							varying_texcoord))), 
				normalize(
					varying_light_position - varying_vertex_position)), 
			0.0, 
			1.0);

	// Calculating The Final Color
	gl_FragColor = 
		ambient_color + diffuse_color * diffuse_term;
}
