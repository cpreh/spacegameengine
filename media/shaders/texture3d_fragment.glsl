#version 140

$$$HEADER$$$

in vec3 position_interp;
out vec4 frag_color;

void
main()
{
	float gray = 
		texture(
			tex,
			position_interp).r;

	gray = gray * gray * gray;

	frag_color =
		vec4(gray,gray,gray,gray);
}
