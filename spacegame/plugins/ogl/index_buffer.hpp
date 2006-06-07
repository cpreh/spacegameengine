#ifndef SGE_OGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OGL_INDEX_BUFFER_HPP_INCLUDED

#include "../../core/renderer/index_buffer.hpp"
#include "./basic_arb_buffer.hpp"

namespace sge
{
	namespace ogl
	{
		class index_buffer : public basic_arb_buffer<sge::index_buffer,GL_ELEMENT_ARRAY_BUFFER_ARB> {
		public:
			index_buffer(const size_type sz, const resource_flag_t flags, const const_pointer src)
				: basic_arb_buffer<sge::index_buffer,GL_ELEMENT_ARRAY_BUFFER_ARB>(sz,sge::index_buffer::stride,flags,src) {}
			iterator begin() { return raw_data(); }
			const_iterator begin() const { return raw_data(); }
		};
	}
}

#endif

