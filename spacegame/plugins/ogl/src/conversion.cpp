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

template<> GLenum sge::ogl::convert_cast(const bool_state& state)
{
	switch(state) {
	case BS_EnableAlphaBlending:
		return GL_BLEND;
	case BS_EnableZBuffer:
		return GL_DEPTH_TEST;
	case BS_EnableStencil:
		return GL_STENCIL_TEST;
	case BS_EnableFog:
		return GL_FOG;
	default:
		throw std::logic_error("unsupported bool_state");
	}
}

template<> GLenum sge::ogl::convert_cast(const filter_arg& arg)
{
	switch(arg) {
	case FARG_MinFilter:
		return GL_TEXTURE_MIN_FILTER;
	case FARG_MagFilter:
		return GL_TEXTURE_MAG_FILTER;
	default:
		throw std::logic_error("unsupported filter_arg");
	}
}

template<> GLenum sge::ogl::convert_cast(const filter_arg_value& arg)
{
	switch(arg) {
	case FARGV_Point:
		return GL_NEAREST;
	case FARGV_Linear:
		return GL_LINEAR;
	default:
		throw std::logic_error("unsupported filter_arg_value");
	}
}

template<> GLenum sge::ogl::convert_cast(const matrix_usage& u)
{
	switch(u) {
	case MU_Transform:
		return GL_MODELVIEW;
	case MU_Projection:
		return GL_PROJECTION;
	default:
		throw std::logic_error("unsupported matrix_usage");
	}
}
