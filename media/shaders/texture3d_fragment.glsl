#version 140

$$$HEADER$$$

in vec3 position_interp;
out vec4 frag_color;

void
main()
{
	//float depth = position_interp.z / position_interp.w;
	//depth = depth * depth * depth;
	//frag_color = vec4(depth,depth,depth,0.5);

	float gray = 
		texture(
			tex,
			position_interp).r;

	frag_color =
		vec4(gray,gray,gray,gray);
}
