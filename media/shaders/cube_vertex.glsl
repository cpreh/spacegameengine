#version 120

$$$HEADER$$$

varying vec2 varying_texcoord;
varying vec3 varying_light_position;
varying vec3 varying_vertex_position;

void 
main()
{
	gl_Position = 
		mvp * gl_Vertex;

	vec3 vertex_binormal = 
		cross(
			vertex_normal,
			vertex_tangent);

	vec3 vertex_position = 
		vec3(
			gl_Vertex);

	varying_texcoord = 
		vec2(
			gl_MultiTexCoord0);
	varying_light_position = 
		vec3(
			dot(
				radius * light_position,
				vertex_tangent),
			dot(
				radius * light_position,
				vertex_binormal),
			dot(
				radius * light_position,
				vertex_normal));
	varying_vertex_position = 
		vec3(
			dot(
				vertex_position,
				vertex_tangent),
			dot(
				vertex_position,
				vertex_binormal),
			dot(
				vertex_position,
				vertex_normal));
}
