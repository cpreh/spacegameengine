#version 120

$$$HEADER$$$

in vec3 vertex_normal;

varying vec2 varying_texcoord;
varying vec3 varying_normal;
varying vec3 varying_vertex_to_light_vector;

void 
main()
{
	gl_Position = 
		mvp * gl_Vertex;
	varying_texcoord = 
		vec2(
			gl_MultiTexCoord0);
	varying_normal = 
		vertex_normal;
	varying_vertex_to_light_vector = 
		light_position - 
		vec3(
			gl_Vertex);
	/*
	varying_normal = 
		vec3(
			mv * vec4(vertex_normal,1.0));
	varying_vertex_to_light_vector = 
		vec3(
			mv * vec4(light_position,1.0)) - 
		vec3(
			mv * gl_Vertex);
	*/
}
