in float dim;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_PointSize = dim;
	gl_FrontColor = gl_Color;
}
