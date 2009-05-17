uniform sampler2D tex;

void main()
{
	vec4 sum = vec4(0);
	vec2 texcoord = vec2(gl_TexCoord[0]);

	const int box = 4;

	for(int x = -box; x < box; x++)
	{
		for (int y = -box; y < box; y++)
		{
			vec4 current = texture2D(
				tex,
				vec2(
					texcoord.x+x/1024.0,
					texcoord.y+y/768.0));

			// contrast stuff begin
			/*
			const float coeff = 0.8;
			for (int i = 0; i < 4; ++i)
			{
				float ex = -((current[i]*16.0)-8.0)/coeff;
				current[i] = (1.0/(1.0+exp(ex)));
			}
			*/
			for (int i = 0; i < 4; ++i)
			{
				current[i] = 3.0*current[i]*current[i]-2.0*current[i]*current[i]*current[i];
			}
			// contrast stuff end
			
			sum += current/float(4*box*box);
		}
	}

	gl_FragColor = sum + texture2D(
		tex,
		texcoord);
}
