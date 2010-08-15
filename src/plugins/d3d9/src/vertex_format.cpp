/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../vertex_format.hpp"
#include <fcppt/container/raw_vector_impl.hpp>
#include <sge/exception.hpp>
#include <boost/foreach.hpp>

namespace
{

D3DDECLUSAGE
convert_role (
	sge::renderer::vf::role::type);

BYTE
vertex_type(
	sge::renderer::vf::role::type);

}

sge::d3d9::vertex_format::vertex_format(
	d3d_device_ptr const device_,
	sge::renderer::vf::dynamic_format const &format_)
:
	format_(format_)
{
	container::raw_vector<
		D3DVERTEXELEMENT9
	> vertex_elements;

	renderer::size_type offset = 0;

	renderer::vf::dynamic_ordered_element_list const &elems(
		format_.elements()
	);

	BOOST_FOREACH(
		renderer::vf::dynamic_ordered_element const &e,
		elems
	)
	{
		renderer::vf::role::type const usage(
			e.element().role()
		);

		D3DVERTEXELEMENT9 elem;
		elem.Stream = 0;
		elem.Method = D3DDECLMETHOD_DEFAULT;
		elem.Offset = static_cast<WORD>(offset);
		//elem.Type = vertex_type(usage);
		elem.Usage = convert_role(usage);

		//for(elem.UsageIndex = 0; elem.UsageIndex < e.count(); ++elem.UsageIndex)
		//	vertex_elements.push_back(elem);

		//oi[usage] = offset;
		offset += 0; // size
	}

	D3DVERTEXELEMENT9 const end_token = D3DDECL_END();
	vertex_elements.push_back(end_token);

	IDirect3DVertexDeclaration9 *decl;

	if(
		device_->CreateVertexDeclaration(
			vertex_elements.data(),
			&decl
		) != D3D_OK
	)
		throw exception(
			FCPPT_TEXT("CreateVertexDeclaration() failed!")
		);

	vertex_declaration_.reset(decl);

	//if(D3DXFVFFromDeclarator(&vertex_elements.front(),&fvf) != D3D_OK)
	//	fvf = 0;
	//	FIXME
}

sge::d3d9::d3d_vertex_declaration_ptr const
sge::d3d9::vertex_format::vertex_declaration() const
{
	return vertex_declaration_;
}

sge::renderer::vf::dynamic_format const &
sge::d3d9::vertex_format::format() const
{
	return format_;
}

DWORD sge::d3d9::vertex_format::fvf() const
{
	return fvf_;
}

sge::renderer::size_type
sge::d3d9::vertex_format::stride() const
{
	return format().stride();
}

namespace
{
/*
BYTE
vertex_type(
	sge::renderer::vf::role::type const u)
{
	switch(u) {
	case role::pos:
	case sge::vertex_usage::normal:
		return D3DDECLTYPE_FLOAT3;
	case sge::vertex_usage::tex:
		return D3DDECLTYPE_FLOAT2;
	case sge::vertex_usage::diffuse:
		return D3DDECLTYPE_D3DCOLOR;
	default:
		throw sge::exception(FCPPT_TEXT("Invalid vertex_usage!"));
	}
}
*/

D3DDECLUSAGE
convert_role (
	sge::renderer::vf::role::type const u)
{
	namespace role = sge::renderer::vf::role;

	switch(u) {
	case role::pos:
		return D3DDECLUSAGE_POSITION;
	case role::normal:
		return D3DDECLUSAGE_NORMAL;
	case role::texpos:
		return D3DDECLUSAGE_TEXCOORD;
	case role::color:
		return D3DDECLUSAGE_COLOR;
	default:
		throw sge::exception(
			FCPPT_TEXT("Invalid vertex_usage!")
		);
	}
}

}
