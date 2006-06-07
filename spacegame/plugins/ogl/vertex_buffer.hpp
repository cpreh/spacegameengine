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
				: basic_arb_buffer<sge::vertex_buffer,GL_ARRAY_BUFFER_ARB>(size,format.get_stride(),flags,src), format(format), ogl_format(format) {}
			size_type get_stride() const { return format.get_stride(); }
			const sge::vertex_format& get_vertex_format() const { return format; }
			iterator create_iterator(const pointer p) const { return iterator(p,format.get_stride(),ogl_format.get_oi()); }
			const_iterator create_iterator(const const_pointer p) const { return const_iterator(p,get_stride(),ogl_format.get_oi()); }
			iterator begin() { return create_iterator(raw_data()); }
			const_iterator begin() const { return create_iterator(raw_data()); }

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
