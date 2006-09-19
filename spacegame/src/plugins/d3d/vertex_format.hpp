#ifndef SGE_D3D_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_D3D_VERTEX_FORMAT_HPP_INCLUDED

#include "../../core/renderer/vertex_buffer.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class vertex_format {
public:
	vertex_format(d3d_device_ptr device, const sge::vertex_format& format);
	d3d_vertex_declaration_ptr vertex_declaration() const { return _vertex_declaration; }
	const offset_info& get_offset_info() const { return oi; }
	DWORD fvf() const { return _fvf; }
	vertex_size stride() const { return _stride; }
private:
	d3d_vertex_declaration_ptr _vertex_declaration;
	offset_info                oi;
	DWORD                      _fvf;
	vertex_size                _stride;
};

}
}

#endif
