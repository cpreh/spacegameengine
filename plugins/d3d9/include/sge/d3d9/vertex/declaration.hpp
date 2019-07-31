//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_D3D9_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vertex/d3d_declaration_unique_ptr.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace vertex
{

class declaration
:
	public sge::renderer::vertex::declaration
{
	FCPPT_NONCOPYABLE(
		declaration
	);
public:
	declaration(
		IDirect3DDevice9 &,
		sge::renderer::vertex::declaration_parameters const &
	);

	~declaration();

	IDirect3DVertexDeclaration9 &
	get() const;

	sge::renderer::vf::dynamic::format const &
	format() const;

	sge::renderer::vf::dynamic::stride const
	stride(
		sge::renderer::vf::dynamic::part_index
	) const;

	sge::d3d9::vf::texture_coordinate_count const
	texture_coordinates() const;
private:
	sge::renderer::vf::dynamic::format const format_;

	sge::d3d9::vf::texture_coordinate_count const texture_coordinates_;

	sge::d3d9::vertex::d3d_declaration_unique_ptr const declaration_;
};

}
}
}

#endif
