//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/create_vertex_declaration.hpp>
#include <sge/d3d9/vertex/declaration.hpp>
#include <sge/d3d9/vf/create.hpp>
#include <sge/d3d9/vf/element_vector.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/d3d9/vf/texture_coordinates.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>


sge::d3d9::vertex::declaration::declaration(
	IDirect3DDevice9 &_device,
	sge::renderer::vertex::declaration_parameters const &_parameters
)
:
	sge::renderer::vertex::declaration(),
	format_(
		_parameters.format()
	),
	texture_coordinates_(
		sge::d3d9::vf::texture_coordinates(
			format_
		)
	),
	declaration_(
		sge::d3d9::devicefuncs::create_vertex_declaration(
			_device,
			sge::d3d9::vf::create(
				format_,
				texture_coordinates_
			)
		)
	)
{
}

sge::d3d9::vertex::declaration::~declaration()
{
}

IDirect3DVertexDeclaration9 &
sge::d3d9::vertex::declaration::get() const
{
	return
		*declaration_;
}

sge::renderer::vf::dynamic::format const &
sge::d3d9::vertex::declaration::format() const
{
	return
		format_;
}

sge::renderer::vf::dynamic::stride const
sge::d3d9::vertex::declaration::stride(
	sge::renderer::vf::dynamic::part_index const _part
) const
{
	return
		this->format().parts().at(
			_part.get()
		).stride();
}

sge::d3d9::vf::texture_coordinate_count const
sge::d3d9::vertex::declaration::texture_coordinates() const
{
	return
		texture_coordinates_;
}
