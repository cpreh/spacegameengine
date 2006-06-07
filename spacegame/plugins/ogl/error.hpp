#ifndef SGE_OGL_ERROR_HPP_INCLUDED
#define SGE_OGL_ERROR_HPP_INCLUDED

#include <GL/gl.h>
#include <iostream>

namespace sge
{
	namespace ogl
	{
		inline bool is_error()
		{
			const GLenum error = glGetError();
			if(error!=GL_NO_ERROR)
				std::cerr << "OpenGL errorcode: " << error << '\n';
			return error!=GL_NO_ERROR;
		}
	}
}

#endif
