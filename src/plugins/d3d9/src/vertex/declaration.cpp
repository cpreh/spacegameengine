/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
