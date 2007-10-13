/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../conversion.hpp"
#include "../../../raw_vector.hpp"
#include "../../../exception.hpp"

namespace
{
	void fill_offset_info(sge::offset_info&, sge::vertex_size offset, sge::vertex_usage::type u);
	BYTE get_vertex_type(sge::vertex_usage::type u);
}

sge::d3d::vertex_format::vertex_format(d3d_device_ptr device, const sge::vertex_format& f)
{
	raw_vector<D3DVERTEXELEMENT9> vertex_elements;

	vertex_size offset = 0;
	const sge::vertex_format::usage_list& l = f.elements();
	for(sge::vertex_format::usage_list::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		const vertex_usage::type usage = it->usage();
		D3DVERTEXELEMENT9 elem;
		elem.Stream = 0;
		elem.Method = D3DDECLMETHOD_DEFAULT;
		elem.Offset = static_cast<WORD>(offset);
		elem.Type = get_vertex_type(usage);
		elem.Usage = static_cast<BYTE>(convert_cast<D3DDECLUSAGE>(usage));
		for(elem.UsageIndex = 0; elem.UsageIndex < it->count(); ++elem.UsageIndex)
			vertex_elements.push_back(elem);
		fill_offset_info(oi,offset,usage);
		offset += it->stride();
	}
	_stride = offset;
	
	const D3DVERTEXELEMENT9 end_token = D3DDECL_END();
	vertex_elements.push_back(end_token);

	IDirect3DVertexDeclaration9* decl;
	if(device->CreateVertexDeclaration(&vertex_elements.front(),&decl) != D3D_OK)
		throw exception("CreateVertexDeclaration() failed!");
	_vertex_declaration.reset(decl);

	//if(D3DXFVFFromDeclarator(&vertex_elements.front(),&fvf) != D3D_OK)
	//	fvf = 0;
	//	FIXME
}

namespace
{
	BYTE get_vertex_type(const sge::vertex_usage::type u)
	{
		switch(u) {
		case sge::vertex_usage::pos:
		case sge::vertex_usage::normal:
			return D3DDECLTYPE_FLOAT3;
		case sge::vertex_usage::tex:
			return D3DDECLTYPE_FLOAT2;
		case sge::vertex_usage::diffuse:
			return D3DDECLTYPE_D3DCOLOR;
		default:
			throw sge::exception("Invalid vertex_usage!");
		}
	}
}
