uniform sampler2D tex;

void main()
{
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
	//gl_FragColor = vec4(gl_PointCoord.x,0.0,0.0,1.0);
	vec4 tex_color = 
		texture(
			tex,
			gl_PointCoord);
	gl_FragColor = 
		tex_color * gl_Color;
		//tex_color;
		//gl_Color;
}
