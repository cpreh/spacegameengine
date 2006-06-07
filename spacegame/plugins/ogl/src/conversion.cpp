#include "../conversion.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

GLuint sge::ogl::convert_lock_flags(const lock_flag_t f)
{
	if(f & LF_Discard)
		return GL_WRITE_ONLY_ARB;
	return GL_READ_WRITE_ARB;
}

GLuint sge::ogl::convert_resource_flags(const resource_flag_t f)
{
	if(f & RF_Dynamic)
		return GL_DYNAMIC_DRAW_ARB;
	return GL_STATIC_DRAW_ARB;
}

template<> GLenum sge::ogl::convert_cast(const primitive_type& t)
{
	switch(t) {
	case PT_Point:
		return GL_POINT;
	case PT_Line:
		return GL_LINES;
	case PT_LineStrip:
		return GL_LINE_STRIP;
	case PT_Triangle:
		return GL_TRIANGLES;
	case PT_TriangleStrip:
		return GL_TRIANGLE_STRIP;
	case PT_TriangleFan:
		return GL_TRIANGLE_FAN;
	default:
		throw std::logic_error("unsupported primitive_type");
	}
}
