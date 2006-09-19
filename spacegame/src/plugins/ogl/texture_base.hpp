#ifndef SGE_OGL_TEXTURE_BASE_HPP_INCLUDED
#define SGE_OGL_TEXTURE_BASE_HPP_INCLUDED

#include <GL/gl.h>

namespace sge
{
namespace ogl
{

class texture_base {
public:
	GLenum get_type() const { return type; }
	virtual void bind_me() const = 0;
	virtual ~texture_base() {}
protected:
	texture_base(const GLenum type) : type(type) {}
	GLuint id;
private:
	GLenum type;
};

}
}

#endif
