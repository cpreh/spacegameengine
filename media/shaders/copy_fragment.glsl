#version 140

$$$HEADER$$$

out vec4 frag_color;

void
main()
{
	vec2 normalized = 
		gl_FragCoord.xy/target_size;

	//normalized = vec2(normalized.x,1.0 - normalized.y);

	frag_color = 
		texture(
			tex,
			normalized);
}
