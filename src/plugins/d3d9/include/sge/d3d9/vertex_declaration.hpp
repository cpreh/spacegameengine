/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


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
		IDirect3DDevice9 *,
		sge::renderer::vf::dynamic::format const &
	);

	~vertex_declaration();

	IDirect3DVertexDeclaration9 *
	get() const;

	sge::renderer::vf::dynamic::format const &
	format() const;

	renderer::size_type
	stride(
		renderer::vf::dynamic::part_index
	) const;
private:
	sge::renderer::vf::dynamic::format const format_;

	typedef fcppt::scoped_ptr<
		IDirect3DVertexDeclaration9,
		fcppt::com_deleter
	> d3d_scoped_vertex_declaration_ptr;

	d3d_scoped_vertex_declaration_ptr declaration_;
};

}
}

#endif
