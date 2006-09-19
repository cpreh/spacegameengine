#ifndef SGE_OGL_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_OGL_VERTEX_BUFFER_HPP_INCLUDED

#include "../../core/renderer/vertex_buffer.hpp"
#include "./basic_arb_buffer.hpp"
#include "./vertex_format.hpp"

namespace sge
{
namespace ogl
{

class vertex_buffer : public basic_arb_buffer<sge::vertex_buffer,GL_ARRAY_BUFFER_ARB> {
public:
	vertex_buffer(const size_type size, const sge::vertex_format& format,
		      const resource_flag_t flags, const const_pointer src)
		: basic_arb_buffer<sge::vertex_buffer,GL_ARRAY_BUFFER_ARB>(size,format.stride(),flags,src), format(format), ogl_format(format) {}
		
	size_type stride() const { return format.stride(); }
	const sge::vertex_format& get_vertex_format() const { return format; }
	iterator create_iterator(const pointer p) { return iterator(p,format.stride(),ogl_format.offsets()); }
	const_iterator create_iterator(const const_pointer p) const { return const_iterator(p,stride(),ogl_format.offsets()); }
	iterator begin() { return create_iterator(data()); }
	const_iterator begin() const { return create_iterator(data()); }

	void set_format()
	{
		bind_me();
		ogl_format.use_me();
	}
private:
	sge::vertex_format format;
	vertex_format ogl_format;
};

}
}

#endif
