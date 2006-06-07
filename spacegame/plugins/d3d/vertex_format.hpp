#ifndef SGE_D3D_VERTEXFORMAT_HPP_INCLUDED
#define SGE_D3D_VERTEXFORMAT_HPP_INCLUDED

#include "../../core/renderer/vertex_buffer.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
	namespace d3d
	{
		class vertex_format {
		public:
			vertex_format(d3d_device_ptr device, const sge::vertex_format& format);
			d3d_vertex_declaration_ptr get_vertex_declaration() const { return vertex_declaration; }
			const offset_info& get_offset_info() const { return oi; }
			DWORD get_fvf() const { return fvf; }
			vertex_size get_stride() const { return stride; }
		private:
			d3d_vertex_declaration_ptr vertex_declaration;
			offset_info                oi;
			DWORD                      fvf;
			vertex_size                stride;
		};
	}
}

#endif
