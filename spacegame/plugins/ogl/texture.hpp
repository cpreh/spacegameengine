#ifndef SGE_OGL_TEXTURE_HPP_INCLUDED
#define SGE_OGL_TEXTURE_HPP_INCLUDED

#include "../../core/renderer/texture.hpp"
#include "./basic_texture.hpp"
#include "./error.hpp"

namespace sge
{
namespace ogl
{

class texture : public basic_texture<sge::texture,GL_TEXTURE_2D> {
public:
	texture(const const_pointer src, const size_type nwidth, const size_type nheight, const unsigned mipmaps, const resource_flag_t flags)
		: basic_texture<sge::texture,GL_TEXTURE_2D>(nwidth*nheight,mipmaps,flags), _width(nwidth), _height(nheight)
	{
		set_data(src);
	}
	size_type width() const { return _width; }
	size_type height() const { return _height; }
	size_type size() const { return width()*height(); }
	void set_data(const const_pointer src, const lock_rect* const r = 0)
	{
		bind_me();
		const GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE;
		if(!r)
			glTexImage2D(GL_TEXTURE_2D,0,4,width(),height(),0,format,type,src);
		else
			glTexSubImage2D(GL_TEXTURE_2D,0,r->left,r->top,r->right-r->left,r->bottom-r->top,format,type,src);
		if(is_error())
			throw std::runtime_error("glTex(Sub)Image2D() failed!");
	}
private:
	const size_type _width, _height;
};

}
}

#endif

