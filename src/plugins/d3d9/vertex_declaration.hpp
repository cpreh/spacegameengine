/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_D3D9_VERTEX_DECLARATION_HPP_INCLUDED

#include "d3d_device_ptr.hpp"
#include "d3d_vertex_declaration_ptr.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{

class vertex_declaration
:
	public sge::renderer::vertex_declaration
{
	FCPPT_NONCOPYABLE(
		vertex_declaration
	);
public:
	vertex_declaration(
		d3d9::d3d_device_ptr,
		sge::renderer::vf::dynamic::format const &
	);

	~vertex_declaration();

	d3d9::d3d_vertex_declaration_ptr const
	get() const;

	sge::renderer::vf::dynamic::format const &
	format() const;

	renderer::size_type
	stride(
		renderer::vf::dynamic::part_index
	) const;
private:
	sge::renderer::vf::dynamic::format const format_;

	d3d9::d3d_vertex_declaration_ptr declaration_;
};

}
}

#endif
